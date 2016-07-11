#include <iostream>
#include <gflags/gflags.h>
#include <glog/logging.h>

#include "base/time/scoped_time.h"
#include "net/socket/socket_factory.h"

DEFINE_int32(port, 8000, "port");

using namespace std;

int main()
{
    net::TCPClientSocket socket = net::SocketFactory::instance()->make_tcp_client_socket();
    CHECK(socket.set_tcpnodelay());
    CHECK(socket.connect("127.0.0.1", FLAGS_port));

    char buf[1024] = "foobar";

    double duration;
    {
        base::ScopedTime st(&duration);
        CHECK_EQ(socket.write(buf, 7), 7);
        CHECK_EQ(socket.read(buf, 7), 7);
    }

    cout << buf;
    cout << "duration: " << (duration * 1000000) << endl;

    return 0;
}
