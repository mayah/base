#include "net/socket/socket_factory.h"

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

UnixDomainClientSocket SocketFactory::make_unix_domain_client_socket()
{
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        PLOG(ERROR) << "failed to make socket";
        return UnixDomainClientSocket(INVALID_SOCKET);
    }

    return UnixDomainClientSocket(sock);
}

UnixDomainServerSocket SocketFactory::make_unix_domain_server_socket()
{
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        PLOG(ERROR) << "failed to make socket";
        return UnixDomainServerSocket(INVALID_SOCKET);
    }

    return UnixDomainServerSocket(sock);
}

} // namespace net
