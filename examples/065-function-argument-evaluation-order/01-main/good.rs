// Rust evaluates function arguments left to right, and the language guarantees it.
fn main() {
    let mut counter = 0;
    let mut next = || { counter += 1; counter };
    println!("a = {}, b = {}", next(), next()); // always a = 1, b = 2
}
