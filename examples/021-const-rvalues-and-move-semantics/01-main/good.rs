// Moves are the default in Rust and are bitwise relocations; `let x = y;` of a non-Copy value moves,
// regardless of whether the binding was declared `mut`. A "const rvalue that silently copies" cannot exist:
// copying requires an explicit `.clone()`.
struct Blob {
    data: String,
}

fn main() {
    let original = Blob { data: "0123456789012345678901234567890123456789".to_string() };
    let taken = original; // move
    // println!("{}", original.data.len()); // error[E0382]: borrow of moved value: `original`
    println!("{}", taken.data.len());
}
