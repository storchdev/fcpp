// with_capacity only reserves; indexing a missing element is a bounds-checked panic, not undefined behavior.
fn main() {
    let mut v: Vec<i32> = Vec::with_capacity(5);
    println!("len = {}, capacity >= 5: {}", v.len(), v.capacity() >= 5);
    // v[0] = 1;                  // panics: index out of bounds: the len is 0 but the index is 0
    v.resize(5, 0);
    for i in 0..5 { v[i] = (i * i) as i32; }
    println!("{:?}", v);
}
