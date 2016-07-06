fn fib(n: i32) -> i32 {
    match n {
        0 | 1 => 1,
        _ => fib(n - 1) + fib(n - 2),
    }
}

fn main() {
    for n in 0..40 {
        println!("fib({}) = {}", n, fib(n))
    }
}
