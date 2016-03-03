#include "net/socket_factory.h"

#include <sys/socket.h>

#include "glog/logging.h"

namespace net {

SocketFactory* SocketFactory::instance()
{
    static SocketFactory instance;
    return &instance;
}

Socket SocketFactory::make()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        PLOG(ERROR) << "failed to make socket";
        return Socket(INVALID_SOCKET);
    }

    return Socket(sock);
}

} // namespace net
