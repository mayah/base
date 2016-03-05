#include "net/unix_domain_socket.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <utility>

#include <glog/logging.h>

namespace net {

UnixDomainSocket::UnixDomainSocket(UnixDomainSocket&& socket) :
    Socket(std::move(socket))
{
}

UnixDomainSocket::~UnixDomainSocket()
{
}

bool UnixDomainSocket::connect(const char* path)
{
    if (strlen(path) >= 108) {
        LOG(ERROR) << "path too long: size=" << strlen(path);
        return false;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, 108);

    if (::connect(sd_, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        PLOG(ERROR) << "failed to connect"
                    << " path=" << path;
        return false;
    }

    return true;
}

bool UnixDomainSocket::bind(const char* path)
{
    DCHECK(valid());

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, 108);

    if (::bind(sd_, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)) < 0) {
        PLOG(ERROR) << "failed to bind"
                    << " sd=" << sd_
                    << " path=" << path;
        return false;
    }

    return true;
}

bool UnixDomainSocket::listen(int backlog)
{
    if (::listen(sd_, backlog) < 0) {
        PLOG(ERROR) << "listen"
                    << " sd=" << sd_
                    << " backlog=" << backlog;
        return false;
    }

    return true;
}

AcceptedUnixDomainSocket UnixDomainSocket::accept()
{
    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t addr_len = sizeof(addr);

    int fd = ::accept(sd_, reinterpret_cast<struct sockaddr*>(&addr), &addr_len);
    if (fd < 0) {
        PLOG(ERROR) << "failed to accept";
        return AcceptedUnixDomainSocket(INVALID_SOCKET);
    }

    return AcceptedUnixDomainSocket(fd);
}

} // namespace net
