#include <iostream>

#include "lib/terminal/scoped_noncanonical_terminal.h"

int main()
{
    terminal::ScopedNonCanonicalTerminal term;
    while (true) {
        char c;
        if (!term.read_byte(&c)) {
            perror("read");
            break;
        }

        std::cout << "READ: " << c << ' ' << static_cast<int>(c) << std::endl;
    }

    return 0;
}
