// Integer division by zero panics in Rust (it is never UB); checked_div makes the failure a value.
fn average(total: i32, count: i32) -> Option<i32> {
    total.checked_div(count)
}

fn main() {
    let count = std::env::args().count() as i32 - 1;   // 0 when run without arguments
    println!("{:?}", average(10, count));              // None
    // 10 / count   // panics: "attempt to divide by zero"
}
