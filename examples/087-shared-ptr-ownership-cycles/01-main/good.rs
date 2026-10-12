// Rc cycles leak in safe Rust too; Weak is the non-owning back-link.
use std::cell::RefCell;
use std::rc::{Rc, Weak};

struct Node {
    next: RefCell<Option<Rc<Node>>>,
    prev: RefCell<Weak<Node>>,
}
impl Drop for Node { fn drop(&mut self) { println!("drop Node"); } }

fn main() {
    let a = Rc::new(Node { next: RefCell::new(None), prev: RefCell::new(Weak::new()) });
    let b = Rc::new(Node { next: RefCell::new(None), prev: RefCell::new(Weak::new()) });
    *a.next.borrow_mut() = Some(Rc::clone(&b));
    *b.prev.borrow_mut() = Rc::downgrade(&a);
    println!("a strong={} weak={}, b strong={}", Rc::strong_count(&a), Rc::weak_count(&a), Rc::strong_count(&b));
}
