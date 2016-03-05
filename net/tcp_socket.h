#ifndef NET_TCP_SOCKET_H_
#define NET_TCP_SOCKET_H_

#include "net/socket.h"

namespace net {

class TCPSocket;
typedef TCPSocket AcceptedTCPSocket;

class TCPSocket : public Socket {
public:
    TCPSocket(TCPSocket&& socket);
    ~TCPSocket() override;

    bool connect(const char* host, int port);

    bool bind_any(int port);
    bool listen(int backlog);

    AcceptedTCPSocket accept();

    bool set_tcpnodelay();

private:
    explicit TCPSocket(SocketDescriptor sd) : Socket(sd) {}

    friend class SocketFactory;
};

} // namespace net

#endif // NET_TCP_SOCKET_H_
