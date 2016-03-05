#ifndef NET_SOCKET_FACTORY_H_
#define NET_SOCKET_FACTORY_H_

#include "base/macros.h"
#include "net/tcp_socket.h"

namespace net {

class SocketFactory {
public:
    static SocketFactory* instance();

    // Returns TCP socket. If failed, socket will be invalid.
    TCPSocket make_tcp_socket();

private:
    SocketFactory() {}
    DISALLOW_COPY_AND_ASSIGN(SocketFactory);
};

} // namespace net

#endif // NET_SOCKET_FACTORY_H_
