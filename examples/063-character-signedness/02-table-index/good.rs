// A byte is a u8, so indexing a 256-entry table is always in range.
fn main() {
    let text = b"caf\xFF";
    let mut counts = [0i32; 256];
    for &b in text {
        counts[usize::from(b)] += 1;
    }
    println!("{}", counts[usize::from(b'c')]);
}
