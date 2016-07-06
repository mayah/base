use std::io;
use std::str::FromStr;
use std::fmt::Debug;

// TODO(mayah): using char iterator is desired, however, it's unstable.
pub struct Scanner<I> {
    bi: I, // bytes iterator
}

fn is_whitespace(b: u8) -> bool {
    b == b' ' || b == b'\t' || b == b'\r' || b == b'\n'
}

impl<R: io::Read> Scanner<io::Bytes<R>> {
    pub fn new(reader: R) -> Scanner<io::Bytes<R>> {
        Scanner {
            bi: reader.bytes(),
        }
    }

    pub fn next<T>(&mut self) -> Option<T> where T: FromStr + Debug, <T as FromStr>::Err: Debug {
        self.next_token().map(|x| x.parse::<T>().unwrap())
    }

    fn next_token(&mut self) -> Option<String> {
        let mut result: Vec<u8> = Vec::new();
        loop {
            match self.bi.next() {
                None => {
                    if result.len() > 0 {
                        return Some(String::from_utf8(result).unwrap());
                    } else {
                        return None;
                    }
                },
                Some(Ok(c)) => {
                    if is_whitespace(c) {
                        if result.len() > 0 {
                            return Some(String::from_utf8(result).unwrap());
                        } else {
                            continue;
                        }
                    } else {
                        result.push(c);
                    }
                },
                Some(Err(_)) => {
                    // TODO(mayah): Should return err.
                    return None;
                },
            }
        }
    }
}

pub fn from_stdin() -> Scanner<io::Bytes<io::Stdin>> {
    Scanner::new(io::stdin())
}
