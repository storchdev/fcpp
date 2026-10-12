// Lossy conversions are explicit (`as`) or fallible (`try_from`); nothing narrows silently.
fn main() {
    let ratio = 99.9_f64;
    let percent = ratio.round() as i32; // 100; the `as` is visible in review

    let raw: i32 = 300;
    match u8::try_from(raw) {
        Ok(level) => println!("level={level}"),
        Err(e) => println!("300 does not fit in u8: {e}"),
    }

    let big: i64 = 5_000_000_000;
    println!("percent={percent} fits_in_i32={}", i32::try_from(big).is_ok());
}
