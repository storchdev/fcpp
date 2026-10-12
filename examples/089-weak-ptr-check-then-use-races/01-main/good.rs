// Weak::upgrade is the only way to reach the value, and it returns Option<Arc<T>>: there is no separate "expired" check to race.
use std::sync::{Arc, Weak};
use std::thread;

struct Data { value: i32 }

fn main() {
    let owner = Arc::new(Data { value: 42 });
    let w: Weak<Data> = Arc::downgrade(&owner);
    let sp = w.upgrade();                      // Some(Arc) keeps the value alive, or None
    let t = thread::spawn(move || drop(owner));
    match sp {
        Some(sp) => println!("value = {}", sp.value),
        None => println!("already gone"),
    }
    t.join().unwrap();
}
