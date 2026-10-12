// In Rust, a struct literal is just an expression: you evaluate field expressions in the
// order you write them, and you cannot read a field of a struct that doesn't exist yet.
struct Buffer {
    size: usize,
    data: Box<[i32]>,
}

impl Buffer {
    fn new(n: usize) -> Self {
        Buffer { size: n, data: vec![0; n].into_boxed_slice() }
    }
}

fn main() {
    let mut b = Buffer::new(8);
    b.data[7] = 1;
    println!("size={} last={}", b.size, b.data[7]);
}
