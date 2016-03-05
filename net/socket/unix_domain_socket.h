#ifndef NET_UNIX_DOMAIN_SOCKET_H_
#define NET_UNIX_DOMAIN_SOCKET_H_

#include "base/macros.h"
#include "net/socket/socket.h"

namespace net {

class UnixDomainSocket;
typedef UnixDomainSocket AcceptedUnixDomainSocket;

class UnixDomainSocket : public Socket {
public:
    UnixDomainSocket(UnixDomainSocket&& socket);
    ~UnixDomainSocket() override;

    bool connect(const char* path);

    bool bind(const char* path);
    bool listen(int backlog);

    AcceptedUnixDomainSocket accept();

private:
    explicit UnixDomainSocket(SocketDescriptor sd) : Socket(sd) {}

    friend class SocketFactory;
    DISALLOW_COPY_AND_ASSIGN(UnixDomainSocket);
};

}

#endif // NET_UNIX_DOMAIN_SOCKET_H_
