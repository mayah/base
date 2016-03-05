#include "net/tcp_socket.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "glog/logging.h"

namespace net {

TCPSocket::TCPSocket(TCPSocket&& socket) :
    Socket(std::move(socket))
{
}

TCPSocket::~TCPSocket()
{
}

bool TCPSocket::connect(const char* host, int port)
{
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = PF_INET;
    client_addr.sin_addr.s_addr = inet_addr(host);
    client_addr.sin_port = htons(port);

    if (::connect(sd_, reinterpret_cast<struct sockaddr*>(&client_addr), sizeof(client_addr)) < 0) {
        PLOG(ERROR) << "connect"
                    << " host=" << host
                    << " port=" << port;
        return false;
    }

    return true;
}

bool TCPSocket::bind_any(int port)
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

bool TCPSocket::listen(int backlog)
{
    if (::listen(sd_, backlog) < 0) {
        PLOG(ERROR) << "listen"
                    << " socket=" << sd_
                    << " backlog=" << backlog;
        return false;
    }
    return true;
}

AcceptedTCPSocket TCPSocket::accept()
{
    struct sockaddr_in writer_addr;
    socklen_t writer_len;
    int new_fd = ::accept(sd_, reinterpret_cast<struct sockaddr*>(&writer_addr), &writer_len);
    if (new_fd < 0) {
        PLOG(ERROR) << "accept" << " socket=" << sd_;
        return AcceptedTCPSocket(INVALID_SOCKET);
    }

    return AcceptedTCPSocket(new_fd);
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

} // namespace net
