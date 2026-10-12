// Rust has no default arguments; a trait method that wants a default provides it in one place.
trait Greeter {
    fn greet_n(&self, times: u32);
    fn greet(&self) { self.greet_n(1) }
}
struct Derived;
impl Greeter for Derived {
    fn greet_n(&self, times: u32) { println!("Derived::greet({})", times); }
}

fn main() {
    let d = Derived;
    let b: &dyn Greeter = &d;
    b.greet();
    d.greet();
}
