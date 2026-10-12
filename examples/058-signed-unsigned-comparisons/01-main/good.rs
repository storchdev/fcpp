// Rust has no implicit integer conversion: comparing i32 with u32 does not compile.
fn main() {
    let a: i32 = -1;
    let b: u32 = 1;

    // if a < b {}   // error[E0308]: mismatched types: expected `i32`, found `u32`

    println!("-1 < 1u is {}", i64::from(a) < i64::from(b)); // widen both to a type that holds both ranges

    let v = vec![1, 2, 3];
    let idx: i32 = -1;
    match usize::try_from(idx) {
        Ok(i) if i < v.len() => println!("idx {} is in range", idx),
        _ => println!("idx {} is out of range", idx),
    }
}
