#include "net/socket_factory.h"

#include <sys/socket.h>

#include "glog/logging.h"

namespace net {

SocketFactory* SocketFactory::instance()
{
    static SocketFactory instance;
    return &instance;
}

TCPSocket SocketFactory::make_tcp_socket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        PLOG(ERROR) << "failed to make socket";
        return TCPSocket(INVALID_SOCKET);
    }

    return TCPSocket(sock);
}

UnixDomainSocket SocketFactory::make_unix_domain_socket()
{
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        PLOG(ERROR) << "failed to make socket";
        return UnixDomainSocket(INVALID_SOCKET);
    }

    return UnixDomainSocket(sock);
}

} // namespace net
