#include <mt/env/asioStub/ioService.hpp>

#include <algorithm>
#include <gtest/gtest.h>

namespace eMU
{
namespace mt
{
namespace env
{
namespace asioStub
{

using protocol::ReadStream;
using protocol::WriteStream;

io_service::strand::strand(io_service& service) {}

io_service::io_service():
    tcpSocket_(nullptr),
    udpSocket_(nullptr),
    clientTcpSocket_(nullptr),
    connectResult_(true) {}

io_service::~io_service()
{
    this->closeAllTcpConnections();

    if(clientTcpSocket_ != nullptr)
    {
        EXPECT_FALSE(clientTcpSocket_->hasUnreadPayload());
    }
}

size_t io_service::run() { return 0; }
void io_service::stop() {}

void io_service::establishUdpConnection(ip::udp::socket *socket)
{
    udpSocket_ = socket;
}

void io_service::sendTo(const protocol::WriteStream &writeStream)
{
    if(udpSocket_ == nullptr)
    {
        throw NonExistentUdpSocketException();
    }

    udpSocket_->insertPayload(writeStream.getPayload());
}

protocol::ReadStream io_service::receiveFrom()
{
    if(udpSocket_ == nullptr)
    {
        throw NonExistentUdpSocketException();
    }

    return protocol::ReadStream(udpSocket_->getPayload());
}

size_t io_service::establishTcpConnection()
{
    if(tcpSocket_ == nullptr)
    {
        throw AcceptNotStartedException();
    }

    tcpSockets_.push_back(tcpSocket_);
    acceptHandler_(boost::system::error_code());

    return reinterpret_cast<size_t>(tcpSockets_.back());
}

void io_service::closeTcpConnection(size_t hash)
{
    auto it = this->find(hash);

    if(it == tcpSockets_.end())
    {
        throw NonExistentTcpSocketException();
    }

    ASSERT_FALSE((*it)->hasUnreadPayload());
    tcpSockets_.erase(it);
}

void io_service::closeTcpConnection(ip::tcp::socket *socket)
{
    if(socket == clientTcpSocket_)
    {
        ASSERT_FALSE(clientTcpSocket_->hasUnreadPayload());
        clientTcpSocket_ = nullptr;
    }
    else
    {
        this->closeTcpConnection(reinterpret_cast<size_t>(socket));
    }
}

bool io_service::tcpConnectionEstablished(size_t hash) const
{
    return const_cast<io_service*>(this)->find(hash) != tcpSockets_.end();
}

void io_service::queueAccept(ip::tcp::socket &socket, const AcceptHandler &handler)
{
    tcpSocket_ = &socket;
    acceptHandler_ = handler;
}

void io_service::send(size_t hash, const protocol::WriteStream &writeStream)
{
    auto it = this->find(hash);

    if(it == tcpSockets_.end())
    {
        throw NonExistentTcpSocketException();
    }

    (*it)->insertPayload(writeStream.getPayload());
}

protocol::ReadStream io_service::receive(size_t hash)
{
    auto it = this->find(hash);

    if(it == tcpSockets_.end())
    {
        throw NonExistentTcpSocketException();
    }

    return protocol::ReadStream((*it)->getPayload());
}

void io_service::disconnect(size_t hash)
{
    auto it = this->find(hash);

    if(it == tcpSockets_.end())
    {
        throw NonExistentTcpSocketException();
    }

    (*it)->disconnect();
}

void io_service::closeAllTcpConnections()
{
    for(auto tcpSocket : tcpSockets_)
    {
        this->closeTcpConnection(tcpSocket);
    }
}

io_service::TcpSocketsContainer::iterator io_service::find(size_t hash)
{
    return std::find_if(tcpSockets_.begin(), tcpSockets_.end(),
                        [hash](ip::tcp::socket *socket) { return hash == reinterpret_cast<size_t>(socket); });
}

bool io_service::establishClientTcpSocket(ip::tcp::socket &socket)
{
    clientTcpSocket_ = &socket;
    clientTcpSocket_->setOpenState(connectResult_);

    return connectResult_;
}

void io_service::sendToClientTcpSocket(const protocol::WriteStream &writeStream)
{
    if(clientTcpSocket_ == nullptr)
    {
        throw ClientSocketNotConnectedException();
    }

    clientTcpSocket_->insertPayload(writeStream.getPayload());
}

protocol::ReadStream io_service::receiveFromClientTcpSocket()
{
    if(clientTcpSocket_ == nullptr)
    {
        throw ClientSocketNotConnectedException();
    }

    return protocol::ReadStream(clientTcpSocket_->getPayload());
}

void io_service::setConnectResult(bool result)
{
    connectResult_ = result;
}

}
}
}
}
