// Rust rejects use after move at compile time; a value that is reused must be reassigned first.
struct Message {
    text: String,
    priority: i32,
}

fn send(m: Message) {
    println!("sent '{}'", m.text);
}

fn main() {
    let mut m = Message { text: "hello".to_string(), priority: 7 };
    send(m);
    // println!("{}", m.priority);   // error[E0382]: borrow of moved value: `m`
    m = Message { text: String::new(), priority: 0 };   // assign a fresh value: m is usable again
    println!("after reset: priority={}", m.priority);
}
