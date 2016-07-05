use std::io;

#[allow(dead_code)]
pub struct Scanner<R: io::Read> {
    reader: R,

    // buffer. It would be good if we could use the internal buffer of io::BufRead ?
    pos: usize,
    len: usize,
    buf: Box<[u8; 1024]>,
}

#[allow(dead_code)]
impl<R: io::Read> Scanner<R> {
    pub fn new(reader: R) -> Scanner<R> {
        Scanner {
            reader: reader,
            pos: 0,
            len: 0,
            buf: Box::new([0; 1024]),
        }
    }

    pub fn peek(&mut self) -> Option<u8> {
        if self.pos == self.len {
            if !self.fill() {
                return None;
            }
        }

        if self.pos == self.len {
            return None;
        }

        return Some(self.buf[self.pos]);
    }

    pub fn next_byte(&mut self) -> Option<u8> {
        if self.pos == self.len {
            if !self.fill() {
                return None
            }
        }

        if self.pos == self.len {
            return None;
        }

        let u = self.buf[self.pos];
        self.pos += 1;
        return Some(u);
    }

    fn fill(&mut self) -> bool {
        if self.pos != self.len {
            return true
        }

        self.pos = 0;
        self.len = 0;

        loop {
            match self.reader.read(self.buf.as_mut()) {
                Ok(x) => {
                    self.len = x;
                    return true;
                },
                Err(x) => {
                    if x.kind() == io::ErrorKind::Interrupted {
                        continue;
                    } else {
                        return false;
                    }
                }
            }
        }
    }
}

pub fn from_stdin() -> Scanner<io::Stdin> {
    Scanner::new(io::stdin())
}
