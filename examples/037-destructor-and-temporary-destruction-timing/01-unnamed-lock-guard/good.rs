// A Rust MutexGuard is a value too, but the data is only reachable through the guard, so there is no way to
// touch the counter without holding the lock.
use std::sync::{Arc, Mutex};
use std::thread;

fn main() {
    let counter = Arc::new(Mutex::new(0));
    let handles: Vec<_> = (0..2)
        .map(|_| {
            let counter = Arc::clone(&counter);
            thread::spawn(move || {
                for _ in 0..1000 {
                    *counter.lock().unwrap() += 1; // guard is a temporary here too, but it lives for the statement that uses it
                }
            })
        })
        .collect();
    for h in handles {
        h.join().unwrap();
    }
    println!("counter = {}", *counter.lock().unwrap());
}
