// Rust's borrow checker rejects aliasing &mut references, so the "assign an object to itself" call cannot be written.
fn assign(dst: &mut Vec<i32>, src: &mut Vec<i32>) {
    *dst = std::mem::take(src);
}

fn main() {
    let mut b = vec![1, 2, 3];
    let mut a = vec![0];
    assign(&mut a, &mut b);
    // assign(&mut b, &mut b);   // error[E0499]: cannot borrow `b` as mutable more than once at a time
    println!("a={:?} b={:?}", a, b);
}
