extern crate scanner;

#[allow(unused_variables)]
fn main() {
    let mut s = scanner::from_stdin();

    loop {
        match s.next::<String>() {
            Some(x) => println!("{}", x),
            None => break
        }
    }
}
