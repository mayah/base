#include "net/socket.h"

#include "glog/logging.h"

namespace net {

Socket::~Socket()
{
    if (!valid())
        return;

    if (close(fd_) < 0) {
        PLOG(ERROR) << "failed to close socket";
    }
}

} // namespace net
