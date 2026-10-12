// Division never invokes UB in Rust: `/` panics (even in release builds), and checked_div returns None.
fn main() {
    let a = i32::MIN;
    let b: i32 = -(std::env::args().count() as i32);   // -1, but not a constant

    println!("{:?}", a.checked_div(b));      // None
    println!("{}", a.wrapping_div(b));       // -2147483648, if wraparound is what you want

    // a / b            // panics: "attempt to divide with overflow"
}
