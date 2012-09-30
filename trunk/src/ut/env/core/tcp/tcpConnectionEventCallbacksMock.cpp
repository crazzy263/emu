#include <env/core/tcp/tcpConnectionEventCallbacksMock.hpp>

namespace eMU {
namespace ut {
namespace env {
namespace core {
namespace tcp {

void connectionEventCallbacksMock_t::expectCall_connectEvent(eMU::core::network::tcp::connection_t<> &connection) {
    EXPECT_CALL(*this, connectEvent(::testing::Ref(connection)));
}

void connectionEventCallbacksMock_t::expectCall_receiveEvent(eMU::core::network::tcp::connection_t<> &connection) {
    EXPECT_CALL(*this, receiveEvent(::testing::Ref(connection)));
}

void connectionEventCallbacksMock_t::expectCall_closeEvent(eMU::core::network::tcp::connection_t<> &connection) {
    EXPECT_CALL(*this, closeEvent(::testing::Ref(connection)));
}

}
}
}
}
}