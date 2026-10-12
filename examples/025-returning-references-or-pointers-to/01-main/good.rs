// fn make_greeting(name: &str) -> &String {
//     let s = format!("hello, {name}");
//     &s            // error[E0515]: cannot return reference to local variable `s`
// }

fn make_greeting(name: &str) -> String {
    format!("hello, {name}")
}

fn make_tag() -> String {
    "tag-42".to_string()
}

fn main() {
    println!("{}", make_greeting("world"));
    println!("{}", make_tag());
}
