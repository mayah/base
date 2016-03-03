#ifndef NET_SOCKET_H_
#define NET_SOCKET_H_

#include "base/macros.h"

namespace net {

// Socket is TCP socket.
// fd will be closed when Socket is destructed.
class Socket {
public:
    explicit Socket(int fd) : fd_(fd) {}
    ~Socket();

    bool valid() const { return fd_ != INVALID_SOCKET; }

private:
    const int INVALID_SOCKET = -1;
    int fd_;

    DISALLOW_COPY_AND_ASSIGN(Socket);
};

} // namespace net

#endif // NET_SOCKET_H_
