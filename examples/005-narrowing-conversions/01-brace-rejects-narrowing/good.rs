// Rust never converts between numeric types implicitly, so every narrowing is spelled out.
fn main() {
    // let whole: i32 = 3.5;            // error[E0308]: mismatched types (expected `i32`, found floating-point number)
    // let n: i64 = 5; let m: i32 = n;  // error[E0308]: mismatched types (expected `i32`, found `i64`)
    // let level: u8 = 300;             // error: literal out of range for `u8` (deny-by-default lint `overflowing_literals`)

    let whole = 3.5_f64.round() as i32; // `as` is explicit; float -> int saturates and never invokes UB
    let level: u8 = 200;
    let widened: i32 = level.into(); // lossless conversions use From/Into
    println!("{level} {whole} {widened}");
}
