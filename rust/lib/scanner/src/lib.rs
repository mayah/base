use std::io;
use std::collections::VecDeque;

#[allow(dead_code)]
pub struct Scanner<R: io::Read> {
    r: R,

    // buffer. Good if we could use the internal buffer of io::BufRead...
    buf: VecDeque<u8>,
}

impl<R: io::Read> Scanner<R> {
    fn new(reader: R) -> Scanner<R> {
        Scanner {
            r: reader,
            buf: VecDeque::new(),
        }
    }

/*
    /// Returns next character. If EOF, None is returned.
    fn next_char() -> Option<u8> {
        if buf.is_empty() {
    if !fill() {
    return Err(Nothing
}
}
    }
*/

/*
    fn next_int() -> Result<int, Error> {
        let mut sign = 1;
        match next_char() {
            Ok('+') => sign = 1,
            Ok('-') => sign = -1,
            Ok(c) => unputc(c),
            Err(x) => return Err(x)
        }
    }
*/
}

pub fn from_stdin() -> Scanner<io::Stdin> {
    Scanner::new(io::stdin())
}
