use std::io;

pub struct Scanner<R> {
    r: R,
}

impl<R: io::BufRead> Scanner<io::Chars<R>> {
    fn new(reader: R) -> Scanner<io::Chars<R>> {
        Scanner {
            r: reader.chars()
        }
    }
}

pub fn from_stdin() -> Scanner<io::Chars<io::Stdin>> {
    Scanner::new(io::stdin())
}
