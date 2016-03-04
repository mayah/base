#include "net/socket.h"

#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/types.h>

#include "glog/logging.h"

namespace net {

Socket::Socket(Socket&& socket) :
    sd_(socket.sd_)
{
    socket.sd_ = INVALID_SOCKET;
}

Socket::~Socket()
{
    if (!valid())
        return;

    if (close(sd_) < 0) {
        PLOG(ERROR) << "failed to close socket";
    }
}

ssize_t Socket::read(void* buf, size_t size)
{
    return ::read(sd_, buf, size);
}

ssize_t Socket::write(const void* buf, size_t size)
{
    return ::write(sd_, buf, size);
}


bool Socket::bind_any(int port)
{
    struct sockaddr_in reader_addr;
    memset(&reader_addr, 0, sizeof(reader_addr));

    reader_addr.sin_family = PF_INET;
    reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    reader_addr.sin_port = htons(port);

    if (::bind(sd_, reinterpret_cast<struct sockaddr*>(&reader_addr), sizeof(reader_addr)) < 0) {
        PLOG(ERROR) << "bind"
                    << " socket=" << sd_
                    << " port=" << port;
        return false;
    }

    return true;
}

bool Socket::listen(int backlog)
{
    if (::listen(sd_, backlog) < 0) {
        PLOG(ERROR) << "listen"
                    << " socket=" << sd_
                    << " backlog=" << backlog;
        return false;
    }
    return true;
}

AcceptedSocket Socket::accept()
{
    struct sockaddr_in writer_addr;
    socklen_t writer_len;
    int new_fd = ::accept(sd_, reinterpret_cast<struct sockaddr*>(&writer_addr), &writer_len);
    if (new_fd < 0) {
        PLOG(ERROR) << "accept" << " socket=" << sd_;
        return AcceptedSocket(INVALID_SOCKET);
    }

    return AcceptedSocket(new_fd);
}

bool Socket::set_tcpnodelay()
{
    int flag = 1;
    if (setsockopt(sd_, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag)) < 0) {
        PLOG(ERROR) << "failed to set TCP_NODELAY";
        return false;
    }

    return true;
}

} // namespace net
