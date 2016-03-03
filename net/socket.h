#ifndef NET_SOCKET_H_
#define NET_SOCKET_H_

#include "base/macros.h"
#include "net/socket_descriptor.h"

namespace net {

// Socket is TCP socket.
// fd will be closed when Socket is destructed.
class Socket {
public:
    explicit Socket(SocketDescriptor sd) : sd_(sd) {}
    Socket(Socket&& socket);
    ~Socket();

    bool valid() const { return sd_ != INVALID_SOCKET; }

private:
    SocketDescriptor sd_;

    DISALLOW_COPY_AND_ASSIGN(Socket);
};

} // namespace net

#endif // NET_SOCKET_H_
