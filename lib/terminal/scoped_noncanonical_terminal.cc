#include "lib/terminal/scoped_noncanonical_terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

namespace terminal {

ScopedNonCanonicalTerminal::ScopedNonCanonicalTerminal()
{
    tcgetattr(fileno(stdin), &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);
}

ScopedNonCanonicalTerminal::~ScopedNonCanonicalTerminal()
{
    tcsetattr(fileno(stdin), TCSANOW, &oldSettings);
}

bool ScopedNonCanonicalTerminal::read_byte(char* c)
{
    while (true) {
        fd_set set;
        struct timeval tv;

        // max 10 seconds.
        tv.tv_sec = 10;
        tv.tv_usec = 0;

        FD_ZERO(&set);
        FD_SET(fileno(stdin), &set);

        int res = select(fileno(stdin) + 1, &set, NULL, NULL, &tv);
        if (res < 0) {
            return false;
        }
        if (res == 0) {
            // timeout
            continue;
        }

        read(fileno(stdin), c, 1);
        return true;
    }
}

} // namespace terminal
