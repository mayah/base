#ifndef NET_SOCKET_SOCKET_H_
#define NET_SOCKET_SOCKET_H_

#include <sys/types.h>

#include "base/macros.h"
#include "net/socket/socket_descriptor.h"

namespace net {

// fd will be closed when Socket is destructed.
class Socket {
public:
    Socket(Socket&& socket) noexcept;
    virtual ~Socket();

    Socket& operator=(Socket&& socket) noexcept;

    bool valid() const { return sd_ != INVALID_SOCKET; }
    bool close();

    // Returns
    SocketDescriptor descriptor() const { return sd_; }

    // Reads to |buf|.
    ssize_t read(void* buf, size_t size);
    // Reads exactly |size| byte to |buf|. If error happens or
    // EOF comes before really reading |size| byte, false is returned.
    bool read_exactly(void* buf, size_t size);

    ssize_t write(const void* buf, size_t size);
    bool write_exactly(const void* buf, size_t size);

protected:
    explicit Socket(SocketDescriptor sd) : sd_(sd) {}

    SocketDescriptor sd_;

    DISALLOW_COPY_AND_ASSIGN(Socket);
};

} // namespace net

#endif // NET_SOCKET_SOCKET_H_
