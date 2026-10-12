// Option has no unchecked dereference: you must say what happens for None.
fn main() {
    let name: Option<String> = None;
    // let n = (*name).len();   // error[E0614]: type `Option<String>` cannot be dereferenced
    println!("length = {}", name.as_deref().unwrap_or("").len());
    // name.unwrap() would panic: called `Option::unwrap()` on a `None` value
}
