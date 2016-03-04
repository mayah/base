#ifndef NET_SOCKET_H_
#define NET_SOCKET_H_

#include <sys/types.h>

#include "base/macros.h"
#include "net/socket_descriptor.h"

namespace net {

class Socket;
typedef Socket AcceptedSocket;

// Socket is TCP socket.
// fd will be closed when Socket is destructed.
class Socket {
public:
    Socket(Socket&& socket);
    ~Socket();

    bool valid() const { return sd_ != INVALID_SOCKET; }

    ssize_t read(void* buf, size_t size);
    ssize_t write(const void* buf, size_t size);

    bool connect(const char* host, int port);

    bool bind_any(int port);
    bool listen(int backlog);

    AcceptedSocket accept();

    bool set_tcpnodelay();

private:
    explicit Socket(SocketDescriptor sd) : sd_(sd) {}

    SocketDescriptor sd_;

    friend class SocketFactory;
    DISALLOW_COPY_AND_ASSIGN(Socket);
};

} // namespace net

#endif // NET_SOCKET_H_
