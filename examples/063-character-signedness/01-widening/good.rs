// Rust's `u8` is always unsigned, and `char` is a Unicode scalar value, not a byte.
fn main() {
    let b: u8 = 0xE9;
    println!("widened = {}", i32::from(b));         // 233 on every platform
    println!("b == 0xE9: {}", b == 0xE9);
    println!("as char: {}", char::from(b));          // 'é' (U+00E9)
}
