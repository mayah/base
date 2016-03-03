#include "net/socket.h"

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

} // namespace net
