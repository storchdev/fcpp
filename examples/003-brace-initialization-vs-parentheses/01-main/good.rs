// Rust has no constructor overloading, so there is no () vs {} ambiguity:
// the macro or function you call says exactly what the arguments mean.
fn main() {
    let filled = vec![7; 3]; // value ; count  -> [7, 7, 7]
    let elems = vec![3, 7]; // elements       -> [3, 7]
    let zeros = vec![0; 5]; // five zeros
    let one = vec![5]; // one element: 5

    let s = "x".repeat(3);
    println!("{} {} {} {} {}", filled.len(), elems.len(), zeros.len(), one.len(), s);
}
