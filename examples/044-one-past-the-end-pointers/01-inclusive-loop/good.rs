// Slices carry their length, and iterators yield exactly the valid elements; there is no pointer to dereference.
fn main() {
    let a = [1, 2, 3, 4];
    let sum: i32 = a.iter().sum();
    println!("{}", sum);
}
