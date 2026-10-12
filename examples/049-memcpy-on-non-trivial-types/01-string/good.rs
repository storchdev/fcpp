// Rust moves are bitwise copies too, but the source is then considered moved-from and is never dropped,
// so ownership stays unique. A duplicate requires an explicit `clone`.
fn main() {
    let a = String::from("a-long-enough-string-to-defeat-sso-0123456789");
    let b = a.clone();
    println!("{} {}", a, b);
}
