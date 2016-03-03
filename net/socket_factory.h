#ifndef NET_SOCKET_FACTORY_H_
#define NET_SOCKET_FACTORY_H_

#include "base/macros.h"
#include "net/socket.h"

namespace net {

class SocketFactory {
public:
    static SocketFactory* instance();

    Socket make();

private:
    SocketFactory() {}
    DISALLOW_COPY_AND_ASSIGN(SocketFactory);
};

} // namespace net

#endif // NET_SOCKET_FACTORY_H_
