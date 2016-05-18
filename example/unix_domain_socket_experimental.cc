#include <iostream>
#include <thread>

#include "base/concurrent/wait_group.h"
#include "base/strings/string_piece.h"
#include "third_party/glog/glog/logging.h"
#include "net/socket/socket_factory.h"
#include "net/socket/unix_domain_client_socket.h"
#include "net/socket/unix_domain_server_socket.h"

using namespace std;

const char* const UNIX_DOMAIN_SOCKET_PATH = "/tmp/uds-test.sock";

void run_server(concurrent::WaitGroup* wg)
{
    net::UnixDomainServerSocket sock = net::SocketFactory::instance()->make_unix_domain_server_socket();
    CHECK(sock.valid());

    (void)unlink(UNIX_DOMAIN_SOCKET_PATH);
    CHECK(sock.bind(UNIX_DOMAIN_SOCKET_PATH));
    CHECK(sock.listen(5));

    wg->done();

    net::UnixDomainSocket accepted = sock.accept();
    CHECK(accepted.valid());

    CHECK(sock.close());

    char buf[7];
    CHECK(accepted.read_exactly(buf, 7));

    cout << "server: " << strings::StringPiece(buf, 7) << endl;
}

void run_client()
{
    net::UnixDomainClientSocket sock = net::SocketFactory::instance()->make_unix_domain_client_socket();
    CHECK(sock.valid());

    CHECK(sock.connect(UNIX_DOMAIN_SOCKET_PATH));

    cout << "client: foobar" << endl;
    sock.write("foobar", 7);
}

int main()
{
    concurrent::WaitGroup wg;
    wg.add(1);

    thread server_thread(run_server, &wg);
    wg.wait_until_done();

    thread client_thread(run_client);

    client_thread.join();
    server_thread.join();
}
