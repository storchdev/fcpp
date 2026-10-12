use std::sync::atomic::{AtomicBool, AtomicI32, AtomicUsize, Ordering};
use std::sync::Arc;
use std::thread;

fn main() {
    // The racy C++ version does not compile in safe Rust: you cannot share
    // `&mut counter` across threads, and a plain `static mut` needs `unsafe`.
    let counter = Arc::new(AtomicUsize::new(0));
    let ready = Arc::new(AtomicBool::new(false));
    let payload = Arc::new(AtomicI32::new(0));

    let producer = {
        let (ready, payload) = (ready.clone(), payload.clone());
        thread::spawn(move || {
            payload.store(42, Ordering::Relaxed);
            ready.store(true, Ordering::Release);
        })
    };
    let incrementer = {
        let counter = counter.clone();
        thread::spawn(move || {
            for _ in 0..100_000 {
                counter.fetch_add(1, Ordering::Relaxed);
            }
        })
    };
    for _ in 0..100_000 {
        counter.fetch_add(1, Ordering::Relaxed);
    }

    while !ready.load(Ordering::Acquire) {}
    println!("payload={}", payload.load(Ordering::Relaxed));

    producer.join().unwrap();
    incrementer.join().unwrap();
    println!("counter={} (expected 200000)", counter.load(Ordering::Relaxed));
}
