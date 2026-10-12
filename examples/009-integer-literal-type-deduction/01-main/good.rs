// Rust literals have no value-dependent type: an unsuffixed literal is inferred from context
// (defaulting to i32), and an out-of-range literal is a compile-time error, not a silent type change.
fn main() {
    // let big = 2147483648;                // error: literal out of range for `i32` (deny-by-default lint)
    let big = 2_147_483_648_i64; // the suffix (or a type annotation) says what you mean
    let mask: u32 = 0xFFFF_FFFF;

    let status: i32 = -1;
    // if status < mask {}                  // error[E0308]: mismatched types (expected `i32`, found `u32`)
    if i64::from(status) < i64::from(mask) {
        println!("-1 < 0xFFFFFFFF");
    }
    println!("big={big} mask={mask}");
}
