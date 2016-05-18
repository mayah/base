#include "net/socket/unix_domain_client_socket.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <utility>

#include "third_party/glog/glog/logging.h"

namespace net {

UnixDomainClientSocket::UnixDomainClientSocket(UnixDomainClientSocket&& socket) noexcept :
    Socket(std::move(socket))
{
}

UnixDomainClientSocket::~UnixDomainClientSocket()
{
}

UnixDomainClientSocket& UnixDomainClientSocket::operator=(UnixDomainClientSocket&& socket) noexcept
{
    std::swap(sd_, socket.sd_);
    return *this;
}

bool UnixDomainClientSocket::connect(const char* path)
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

} // namespace net
