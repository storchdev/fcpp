// Shifts are checked: `<<` panics in debug builds when the count is too large; checked_shl returns None.
fn main() {
    let n = 31 + std::env::args().count() as u32;      // 32
    println!("{:?}", 1u32.checked_shl(n));             // None
    println!("{}", 1u32.wrapping_shl(n));              // 1: the count is masked to n % 32
}
