// Rust integers do not silently mix signedness, and unsigned subtraction is explicit about underflow.
fn last_index(v: &[i32]) -> Option<usize> {
    v.len().checked_sub(1) // None for an empty slice
}

fn main() {
    let empty: Vec<i32> = Vec::new();
    println!("last_index(empty) = {:?}", last_index(&empty));

    // A reverse range has no "i >= 0" test to get wrong.
    for i in (0..4u32).rev() {
        println!("i = {}", i);
    }

    // `empty.len() - 1` would panic in a debug build and wrap in a release build (-O); it is never UB.
}
