extern crate scanner;

#[allow(unused_variables)]
fn main() {
    let mut s = scanner::from_stdin();

    loop {
        match s.next_byte() {
            Some(c) =>
                print!("{}", c as char),
            None => break
        }
    }
}
