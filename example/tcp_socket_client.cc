#include <iostream>

#include <glog/logging.h>
#include "base/time/scoped_time.h"
#include "net/socket/socket_factory.h"

using namespace std;

int main()
{
    net::TCPClientSocket socket = net::SocketFactory::instance()->make_tcp_client_socket();
    CHECK(socket.valid());
    CHECK(socket.set_tcpnodelay());

    CHECK(socket.connect("127.0.0.1", 8000));

    char buf[1024] = "foobar";

    double duration;
    {
        base::ScopedTime timer(&duration);
        CHECK_EQ(socket.write(buf, 7), 7);
        CHECK_EQ(socket.read(buf, 7), 7);
    }

    cout << buf << endl;
    cout << (duration * 1000000) << " [us]" << endl;

    return 0;
}
