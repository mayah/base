#include <glog/logging.h>

#include "net/socket/socket_factory.h"
#include "net/socket/tcp_server_socket.h"

int main()
{
    net::TCPServerSocket sock = net::SocketFactory::instance()->make_tcp_server_socket();
    CHECK(sock.valid());
    CHECK(sock.set_tcpnodelay());

    CHECK(sock.bind_from_any(8000));
    CHECK(sock.listen(5));

    while (true) {
        net::TCPSocket accepted = sock.accept();
        CHECK(accepted.valid());

        while (true) {
            char buf[8096];
            ssize_t n = accepted.read(buf, 8096);
            if (n < 0) {
                PLOG(ERROR) << "read";
                return 1;
            }

            if (n == 0) {
                return 0;
            }

            CHECK_EQ(accepted.write(buf, n), n);
        }
    }

    return 0;
}
