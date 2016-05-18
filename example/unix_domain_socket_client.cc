#include <iostream>

#include "base/time/scoped_time.h"
#include "third_party/glog/glog/logging.h"
#include "net/socket/socket_factory.h"

const char* const UNIX_DOMAIN_SOCKET_PATH = "/tmp/uds-test.sock";

using namespace std;

int main()
{
    net::UnixDomainClientSocket socket = net::SocketFactory::instance()->make_unix_domain_client_socket();
    CHECK(socket.valid());

    CHECK(socket.connect(UNIX_DOMAIN_SOCKET_PATH));

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
