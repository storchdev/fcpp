// A closure that borrows a local cannot be returned: the borrow checker reports E0373. `move` transfers ownership.
fn make_counter(start: i32) -> impl FnMut() -> i32 {
    let mut count = start;
    // return || { count += 1; count };   // error[E0373]: closure may outlive the current function, but it borrows `count`
    move || {
        count += 1;
        count
    }
}

fn main() {
    let mut next = make_counter(10);
    let a = next();
    let b = next();
    println!("{} {}", a, b);
}
