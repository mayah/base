#include "third_party/glog/glog/logging.h"
#include "net/socket/socket_factory.h"
#include "net/socket/unix_domain_server_socket.h"

const char* const UNIX_DOMAIN_SOCKET_PATH = "/tmp/uds-test.sock";

int main()
{
    net::UnixDomainServerSocket sock = net::SocketFactory::instance()->make_unix_domain_server_socket();
    CHECK(sock.valid());

    (void)unlink(UNIX_DOMAIN_SOCKET_PATH);
    CHECK(sock.bind(UNIX_DOMAIN_SOCKET_PATH));
    CHECK(sock.listen(5));

    while (true) {
        net::UnixDomainSocket accepted = sock.accept();
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
