// Returning a reference to a local is E0515 in Rust; there is no way to write it by accident.
// fn next_id() -> &'static i32 {
//     let id = 42;
//     &id          // error[E0515]: cannot return reference to local variable `id`
// }
fn next_id() -> i32 {
    let mut id = 41;
    id += 1;
    id
}

fn main() {
    println!("{}", next_id());
}
