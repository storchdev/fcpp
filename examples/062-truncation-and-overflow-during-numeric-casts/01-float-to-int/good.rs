// `as` from float to int saturates (NaN becomes 0); it is never UB.
fn main() {
    let big = 1e10 * std::env::args().count() as f64;
    println!("{}", big as i32);                  // 2147483647
    println!("{}", f64::NAN as i32);             // 0
    println!("{:?}", i32::try_from(big as i64)); // Err: the explicit checked route
}
