extern crate hello_lib;

fn main() {
    let hello = hello_lib::greeter::Greeter::new("Hello");
    hello.greet("world");
}
