#include "net/socket/tcp_socket.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "third_party/glog/glog/logging.h"

namespace net {

TCPSocket::TCPSocket(TCPSocket&& socket) noexcept :
    Socket(std::move(socket))
{
}

TCPSocket::~TCPSocket()
{
}

TCPSocket& TCPSocket::operator=(TCPSocket&& socket) noexcept
{
    std::swap(sd_, socket.sd_);
    return *this;
}

bool TCPSocket::set_tcpnodelay()
{
    int flag = 1;
    if (setsockopt(sd_, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag)) < 0) {
        PLOG(ERROR) << "failed to set TCP_NODELAY";
        return false;
    }

    return true;
}

bool TCPSocket::set_reuseaddr()
{
    int yes = 1;
    if (setsockopt(sd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
        PLOG(ERROR) << "failed to set SO_REUSEADDR; sd=" << sd_;
        return false;
    }

    return true;
}

} // namespace net
