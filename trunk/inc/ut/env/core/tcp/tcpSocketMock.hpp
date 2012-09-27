#pragma once

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <gmock/gmock.h>

#include <shared/types.hpp>
#include <env/core/ioServiceStub.hpp>

namespace eMU {
namespace ut {
namespace env {
namespace core {
namespace tcp {

class socketMock_t: private boost::noncopyable {
public:
    class endpointStub_t {
    public:
        class addressStub_t {
        public:
            std::string to_string() const { return "001.200.003.400"; }
        };

        addressStub_t address() { return addressStub_t(); }
    };

    typedef boost::function1<void, const boost::system::error_code&> connectHandler_t;

    socketMock_t(ioServiceStub_t &ioService);

    MOCK_METHOD0(close, void());
    void expectCall_close();

    MOCK_METHOD1(shutdown, void(boost::asio::ip::tcp::socket::shutdown_type type));
    void expectCall_shutdown(boost::asio::ip::tcp::socket::shutdown_type type);

    MOCK_METHOD2(async_receive, void(boost::asio::mutable_buffers_1 &buffer, const ioServiceStub_t::ioHandler_t &handler));
    void expectCall_async_receive();
    void impl_async_receive(boost::asio::mutable_buffers_1 &buffer, const ioServiceStub_t::ioHandler_t &handler);

    MOCK_METHOD2(async_send, void(boost::asio::mutable_buffers_1 &buffer, const ioServiceStub_t::ioHandler_t &handler));
    void expectCall_async_send();
    void impl_async_send(boost::asio::mutable_buffers_1 &buffer, const ioServiceStub_t::ioHandler_t &handler);

    MOCK_METHOD2(async_connect, void(const boost::asio::ip::tcp::endpoint &endpoint, const connectHandler_t &handler));
    void expectCall_async_connect(const boost::asio::ip::tcp::endpoint &endpoint);
    void impl_async_connect(const boost::asio::ip::tcp::endpoint &endpoint, const connectHandler_t &handler);

    endpointStub_t remote_endpoint() const { return endpointStub_t(); }
    ioServiceStub_t& get_io_service() { return ioService_; }

    uint8 *rbuf_;
    size_t rbufSize_;
    ioServiceStub_t::ioHandler_t receiveHandler_;
    
    uint8 *wbuf_;
    size_t wbufSize_;
    ioServiceStub_t::ioHandler_t sendHandler_;

    connectHandler_t connectHandler_;

    ioServiceStub_t &ioService_;
};

}
}
}
}
}