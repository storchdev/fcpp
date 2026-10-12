// Ownership is unique: `drop` consumes the value, and a borrow that is still alive makes the drop a compile error (E0505).
struct Session {
    id: i32,
}

fn main() {
    let s = Session { id: 7 };
    let r = &s;
    // drop(s);                // error[E0505]: cannot move out of `s` because it is borrowed
    println!("session {}", r.id);
}
