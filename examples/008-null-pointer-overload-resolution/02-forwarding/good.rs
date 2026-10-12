// Rust has no null pointer constants and no integer-to-pointer coercion: absence is `Option`,
// and "no next node" has to be written `None` at every call site, including through generic code.
struct Node {
    next: Option<Box<Node>>,
}

fn make<T>(value: T) -> Box<T> {
    Box::new(value)
}

fn main() {
    // let bad = Node { next: 0 };   // error[E0308]: mismatched types (expected `Option<Box<Node>>`, found integer)
    let a = make(Node { next: None });
    let b = make(Node { next: Some(a) });
    println!("{}", b.next.is_some());
}
