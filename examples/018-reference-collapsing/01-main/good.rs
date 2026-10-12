// Rust has no reference collapsing: `&T` and `&mut T` are distinct types and generics never
// silently turn "T" into "a reference to the caller's value". A copy is an explicit `Clone`.
fn bump_copy<T: Clone + std::ops::AddAssign<i32>>(x: &T) -> T {
    let mut copy = x.clone();
    copy += 1;
    copy
}

fn main() {
    let n = 1;
    bump_copy(&n);
    println!("n = {}", n); // 1
}
