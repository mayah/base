#include <iostream>
#include <thread>
#include <vector>

#include "net/socket/socket_factory.h"
#include "net/socket/tcp_server_socket.h"
#include "third_party/glog/glog/logging.h"

class Task {
public:
    Task(net::TCPSocket socket) : socket_(std::move(socket)) {}

    void run();

private:
    net::TCPSocket socket_;
};

void Task::run()
{
    std::cout << "run: sd=" << socket_.descriptor() << std::endl;

    while (true) {
        char buf[8096];
        ssize_t n = socket_.read(buf, 8096);
        if (n < 0) {
            PLOG(ERROR) << "read";
            return;
        }

        if (n == 0) {
            return;
        }

        CHECK_EQ(socket_.write(buf, n), n);
    }
}

int main()
{
    std::vector<std::thread> threads;

    net::TCPServerSocket sock = net::SocketFactory::instance()->make_tcp_server_socket();
    CHECK(sock.valid());
    CHECK(sock.set_tcpnodelay());
    CHECK(sock.set_reuseaddr());

    int port = 8000;

    CHECK(sock.bind_from_any(port));
    CHECK(sock.listen(5));

    std::cout << "waiting port " << port << std::endl;

    while (true) {
        net::TCPSocket accepted = sock.accept();
        CHECK(accepted.valid());

        std::cout << "accepted " << accepted.descriptor() << std::endl;

        Task task(std::move(accepted));

        std::thread th([](Task task) {
            task.run();
        }, std::move(task));

        th.detach();
    }

    return 0;
}
