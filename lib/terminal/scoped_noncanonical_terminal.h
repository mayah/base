#ifndef LIB_TERMINAL_SCOPED_NONCANONICAL_TERMINAL_H_
#define LIB_TERMINAL_SCOPED_NONCANONICAL_TERMINAL_H_

#include <termios.h>

namespace terminal {

// During this instance exists, the terminal becomes non canonical.
// Should not be nested.
class ScopedNonCanonicalTerminal {
public:
    ScopedNonCanonicalTerminal();
    ~ScopedNonCanonicalTerminal();

    bool read_byte(char* c);

private:
  struct termios oldSettings, newSettings;
};

} // namespace terminal

#endif // LIB_TERMINAL_SCOPED_NONCANONICAL_TERMINAL_H_
