// Both arms of an `if` expression must already have the same type; there is no implicit common type.
fn main() {
    let idx: i32 = -1;
    let n: u32 = 5;
    let pick = std::env::args().count() > 0;

    // let m = if pick { idx } else { n };   // error[E0308]: `if` and `else` have incompatible types

    let m = if pick { i64::from(idx) } else { i64::from(n) };
    println!("m = {}, m > 100 is {}", m, m > 100);
}
