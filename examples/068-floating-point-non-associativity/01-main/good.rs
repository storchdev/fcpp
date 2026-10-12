// The grouping you write is the grouping rustc uses: the two results below differ, as in C++.
fn main() {
    let big = 1e16 * std::env::args().count() as f64;
    let (a, b, c) = (big, -big, 1.0);
    println!("(a + b) + c = {}", (a + b) + c); // 1
    println!("a + (b + c) = {}", a + (b + c)); // 0
}
