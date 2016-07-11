#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <spawn.h>
#include <unistd.h>

#include <cstdlib>
#include <memory>
#include <vector>

#include <gflags/gflags.h>

#include "base/time/scoped_time.h"

DEFINE_bool(memory, true, "consume memory");
DEFINE_bool(fd, true, "consume fd");

using namespace std;

const int FORK_NUM = 1000;

bool calculate_fork_performance()
{
    double duration;
    {
        base::ScopedTime st(&duration);
        for (int i = 0; i < FORK_NUM; ++i) {
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                return false;
            }

            if (pid == 0) {
                // child. Exit immediately.
                if (execl("/bin/true", "/bin/true", nullptr) < 0) {
                    perror("execl");
                    _exit(1);
                }
                // ASSERT NOT REACHED.
                _exit(1);
            } else {
                // parent
                int status;
                if (waitpid(pid, &status, 0) < 0) {
                    perror("waitpid");
                    return false;
                }
            }
        }
    }

    printf("duration = %f\n", duration);
    printf("fork/sec = %f\n", FORK_NUM / duration);
    return true;
}

bool calculate_spawn_performance()
{
    double duration;
    {
        base::ScopedTime st(&duration);
        char* argv[2];
        argv[0] = strdup("/bin/true");
        argv[1] = nullptr;
        for (int i = 0; i < FORK_NUM; ++i) {
            pid_t pid;
            if (posix_spawn(&pid, "/bin/true", nullptr, nullptr, argv, nullptr) < 0) {
                perror("posix_spawn");
                free(argv[0]);
                return false;
            }
        }

        free(argv[0]);
    }

    printf("duration = %f\n", duration);
    printf("spawn/sec = %f\n", FORK_NUM / duration);
    return true;
}

void consume_lots_of_memory(vector<unique_ptr<int>>* memory)
{
    for (int i = 0; i < 1024 * 1024; ++i) {
        memory->emplace_back(new int);
    }
}

int main()
{
    if (!calculate_fork_performance()) {
        printf("failed to calculate fork performance (1)");
        return 1;
    }
    if (!calculate_spawn_performance()) {
        printf("failed to calculate fork performance (1)");
        return 1;
    }

    if (FLAGS_fd) {
        // Open 10000 files.
        for (int i = 0; i < 10000; ++i) {
            char buf[80];
            sprintf(buf, "/tmp/hoge/%05d", i);
            if (open(buf, O_RDWR | O_CREAT, 0777) < 0) {
                perror("open");
                return 1;
            }
        }

        printf("FILE DONE\n");
    }

    if (!calculate_fork_performance()) {
        printf("failed to calculate fork performance (2)");
        return 1;
    }
    if (!calculate_spawn_performance()) {
        printf("failed to calculate fork performance (2)");
        return 1;
    }

    vector<unique_ptr<int>> memory;
    if (FLAGS_memory) {
        consume_lots_of_memory(&memory);
        printf("MEMORY DONE\n");
    }

    if (!calculate_fork_performance()) {
        printf("failed to calculate fork performance (3)");
        return 1;
    }
    if (!calculate_spawn_performance()) {
        printf("failed to calculate fork performance (3)");
        return 1;
    }

    return 0;
}
