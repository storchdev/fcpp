// The borrow checker forbids mutating a Vec while a reference into it is alive.
fn main() {
    let mut v: Vec<i32> = (0..4).collect();
    // let first = &v[0];
    // v.push(4);                 // error[E0502]: cannot borrow `v` as mutable because it is also borrowed as immutable
    // println!("first = {}", first);
    v.push(4);
    let first = &v[0];            // borrow after the last modification
    println!("first = {}", first);
}
