#ifndef eMU_CORE_SERVER_HPP
#define eMU_CORE_SERVER_HPP

#include <boost/pool/object_pool.hpp>
#include <boost/lambda/lambda.hpp>
#include "connection.hpp"
#include "userFactory.hpp"

namespace eMU {
namespace core {
namespace network {

template<typename UserImpl,
         typename ConnectionImpl = connection_t<>,
         typename IoServiceImpl = boost::asio::io_service,
         typename AcceptorImpl = boost::asio::ip::tcp::acceptor>
class server_t: public ConnectionImpl::observer_i,
                private boost::noncopyable {
public:
    server_t(IoServiceImpl &ioService,
             uint16 port,
             size_t maxNumOfUsers):
      ioService_(ioService),
      acceptor_(ioService,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      maxNumOfUsers_(maxNumOfUsers),
      usersFactory_(maxNumOfUsers_) {}

    virtual ~server_t() {}

    void queueAccept() {
        ConnectionImpl *connection = connectionsPool_.construct(boost::ref(ioService_), boost::ref(*this));

        if(NULL == connection) {
            LOG_ERROR << "Error in allocating new connection object!" << std::endl;
            return;
        }

        acceptor_.async_accept(connection->socket(),
                               boost::bind(&server_t::acceptHandler,
                                           this,
                                           connection,
                                           boost::asio::placeholders::error));
    }

    virtual bool onConnect(UserImpl *user) = 0;
    virtual void onReceive(UserImpl *user, payload_t &payload) = 0;
    virtual void onClose(UserImpl *user) = 0;
    virtual void onCleanup() = 0;

protected:
    server_t();

    void acceptHandler(ConnectionImpl *connection,
                       const boost::system::error_code &ec) {
        if(!ec) {
            this->connectEvent(connection);
        } else {
            LOG_ERROR << "Error during establishing connection, error: " << ec.message() << std::endl;
        }

        this->queueAccept();
    }

    void connectEvent(ConnectionImpl *connection) {
        if(usersList_.size() >= maxNumOfUsers_) {
            LOG_INFO << "Reached max number of users." << std::endl;
            connection->close();
            return;
        }

        UserImpl *user = usersFactory_.construct();
        if(NULL == user) {
            LOG_ERROR << "Error in allocating new user object, address: " << connection->address() << std::endl;
            connection->close();
            return;
        }

        user->connection(connection);

        if(this->onConnect(user)) {
            usersList_.push_back(user);
            connection->queueReceive();
        } else {
            connection->close();
        }
    }

    void receiveEvent(ConnectionImpl *connection, payload_t &payload) {
        std::vector<UserImpl*>::iterator userIter = std::find_if(usersList_.begin(), usersList_.end(), *boost::lambda::_1 == connection);

        if(usersList_.end() == userIter) {
            LOG_ERROR << "Could not find user by connection, address: " << connection->address() << std::endl;
            connection->close();
            return;
        }

        this->onReceive(*userIter, payload);
    }

    void closeEvent(ConnectionImpl *connection) {
        std::vector<UserImpl*>::iterator userIter = std::find_if(usersList_.begin(), usersList_.end(), *boost::lambda::_1 == connection);

        if(usersList_.end() == userIter) {
            LOG_ERROR << "Could not find user by connection, address: " << connection->address() << std::endl;
            return;
        }

        this->onClose(*userIter);
        usersFactory_.destroy(*userIter);
        usersList_.erase(userIter);
    }

    IoServiceImpl &ioService_;
    AcceptorImpl acceptor_;
    size_t maxNumOfUsers_;
    boost::object_pool<ConnectionImpl> connectionsPool_;
    user::factory_t<UserImpl> usersFactory_;
    std::vector<UserImpl*> usersList_;
};

}
}
}
#endif