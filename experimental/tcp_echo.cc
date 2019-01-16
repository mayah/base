#include "net/socket/socket_factory.h"
#include "third_party/gflags/gflags/gflags.h"
#include "third_party/glog/glog/logging.h"

DEFINE_int32(port, 8000, "port");

int main()
{
    net::TCPServerSocket socket = net::SocketFactory::instance()->make_tcp_server_socket();
    CHECK(socket.set_tcpnodelay());
    CHECK(socket.bind_from_any(FLAGS_port));
    CHECK(socket.listen(1));

    net::TCPSocket accepted = socket.accept();
    CHECK(accepted.set_tcpnodelay());

    while (true) {
        char buf[8024];
        int len = accepted.read(buf, 8024);
        if (len < 0) {
            PLOG(ERROR) << len;
            return EXIT_FAILURE;
        }
        if (len == 0) {
            return EXIT_SUCCESS;
        }

        CHECK_EQ(accepted.write(buf, len), len);
    }
}
