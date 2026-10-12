// Rust has no implicit narrowing; you pick `as` (wraps), try_from (checked) or From (lossless).
fn main() {
    let argc = std::env::args().count() as i64;
    let big = 3_000_000_000i64 * argc;
    println!("{:?}", i32::try_from(big));          // Err(TryFromIntError(()))
    println!("{}", big as i32);                    // -1294967296: `as` wraps

    let len: i32 = -(argc as i32);
    println!("{:?}", usize::try_from(len));        // Err: a negative length cannot become usize
}
