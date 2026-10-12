// Rust's &self gives shared access only: mutating through a field needs &mut, or an explicit interior-mutability type.
use std::cell::Cell;

struct Counter<'a> {
    count: &'a Cell<i32>,      // interior mutability is visible in the type
}

impl<'a> Counter<'a> {
    fn bump(&self) { self.count.set(self.count.get() + 1); }
}

// struct Bad<'a> { count: &'a mut i32 }
// impl<'a> Bad<'a> { fn bump(&self) { *self.count += 1; } }   // error[E0594]: cannot assign to `*self.count`, which is behind a `&` reference

fn main() {
    let shared = Cell::new(0);
    let c = Counter { count: &shared };
    c.bump();
    println!("shared = {}", shared.get());
}
