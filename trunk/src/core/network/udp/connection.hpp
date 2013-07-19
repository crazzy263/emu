#pragma once

#ifdef eMU_UT
#include <ut/env/asioStub/ioService.hpp>
#include <ut/env/asioStub/udp/socket.hpp>
#elif eMU_MT
#include <mt/env/asioStub/ioService.hpp>
#include <mt/env/asioStub/udp/socket.hpp>
#else
#include <boost/asio.hpp>
#endif

#include <boost/noncopyable.hpp>
#include <network/udp/writeBufferFactory.hpp>

namespace eMU {
namespace core {
namespace network {
namespace udp {

#ifdef eMU_UT
namespace asio = eMU::ut::env::asioStub;
#elif eMU_MT
namespace asio = eMU::mt::env::asioStub;
#else
namespace asio = boost::asio;
#endif

class Connection: private boost::noncopyable {
public:
    typedef std::function<void(Connection&, const boost::asio::ip::udp::endpoint&)> ReceiveFromEventCallback;
    typedef std::shared_ptr<asio::ip::udp::socket> SocketPointer;

    Connection(asio::io_service &ioService, uint16_t port);
    Connection(SocketPointer socket);
    virtual ~Connection();

    ReadBuffer& readBuffer();
    void setReceiveFromEventCallback(const ReceiveFromEventCallback &callback);
    void queueReceiveFrom();
    void sendTo(const boost::asio::ip::udp::endpoint &endpoint, const Payload &payload);

private:
    Connection();

    void receiveFromHandler(const boost::system::error_code &errorCode, size_t bytesTransferred);
    void queueSendTo(const boost::asio::ip::udp::endpoint &endpoint, WriteBuffer &writeBuffer);
    void sendToHandler(const boost::asio::ip::udp::endpoint &endpoint, const boost::system::error_code &errorCode, size_t bytesTransferred);

    void errorHandler(const boost::system::error_code &errorCode, const std::string &operationName);

    SocketPointer socket_;
    asio::io_service::strand strand_;
    ReadBuffer readBuffer_;
    WriteBufferFactory writeBufferFactory_;
    boost::asio::ip::udp::endpoint senderEndpoint_;
    ReceiveFromEventCallback receiveFromEventCallback_;
};

}
}
}
}