// Vec::retain removes elements and shrinks the Vec in one step.
fn main() {
    let mut v = vec![1, 2, 3, 2];
    v.retain(|&x| x != 2);
    println!("size = {}: {:?}", v.len(), v);
}
