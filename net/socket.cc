#include "net/socket.h"

#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/types.h>

#include "glog/logging.h"

namespace net {

Socket::Socket(Socket&& socket) :
    sd_(socket.sd_)
{
    socket.sd_ = INVALID_SOCKET;
}

Socket::~Socket()
{
    if (!valid())
        return;

    if (close(sd_) < 0) {
        PLOG(ERROR) << "failed to close socket";
    }
}

bool Socket::set_tcpnodelay()
{
    int flag = 1;
    if (setsockopt(sd_, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag)) < 0) {
        PLOG(ERROR) << "failed to set TCP_NODELAY";
        return false;
    }

    return true;
}

} // namespace net
