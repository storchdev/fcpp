// Rust has the same two-tier rule: `let r = &temp();` extends the temporary, but a temporary passed to a function
// that returns a reference derived from it is freed at the end of the statement.
fn pick(s: &String) -> &String {
    s
}

fn main() {
    let direct = &String::from("a-long-enough-string-to-defeat-sso-0123456789"); // extended to the end of main

    // let via_call = pick(&String::from("a-long-enough-string-to-defeat-sso-0123456789"));
    // println!("{}", via_call);  // error[E0716]: temporary value dropped while borrowed
    let owned = String::from("a-long-enough-string-to-defeat-sso-0123456789");
    let via_call = pick(&owned); // name the value so it outlives the borrow

    println!("{} {}", direct, via_call);
}
