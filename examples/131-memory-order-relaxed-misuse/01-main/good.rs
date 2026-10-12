// Safe Rust cannot share a plain mutable payload between threads: the payload must be atomic, locked, or `unsafe`.
use std::sync::atomic::{AtomicBool, AtomicI32, Ordering};
use std::sync::Arc;
use std::thread;

static mut PAYLOAD_PLAIN: i32 = 0;

fn main() {
    // PAYLOAD_PLAIN = 42;          // error[E0133]: use of mutable static is unsafe and requires unsafe function or block
    let _ = unsafe { PAYLOAD_PLAIN };

    let payload = Arc::new(AtomicI32::new(0));
    let ready = Arc::new(AtomicBool::new(false));
    let (p, r) = (payload.clone(), ready.clone());
    let producer = thread::spawn(move || {
        p.store(42, Ordering::Relaxed);
        r.store(true, Ordering::Release);          // publishes the relaxed store above
    });
    let (p, r) = (payload.clone(), ready.clone());
    let consumer = thread::spawn(move || {
        while !r.load(Ordering::Acquire) {}        // synchronises with the release store
        println!("payload = {}", p.load(Ordering::Relaxed));
    });
    producer.join().unwrap();
    consumer.join().unwrap();
}
