// Vec::retain filters in place; erasing inside a for loop over the same Vec does not borrow-check.
fn main() {
    let mut v = vec![2, 4, 6, 1];
    // for x in v.iter() { if x % 2 == 0 { v.remove(0); } }   // error[E0502]: cannot borrow `v` as mutable because it is also borrowed as immutable
    v.retain(|x| x % 2 != 0);
    println!("size = {}: {:?}", v.len(), v);
}
