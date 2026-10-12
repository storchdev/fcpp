// Box<dyn Trait> always drops the concrete type: there is no way to forget the "virtual destructor".
trait Base {}
struct Derived { payload: String }
impl Base for Derived {}
impl Drop for Derived {
    fn drop(&mut self) { println!("drop Derived ({} bytes)", self.payload.len()); }
}

fn main() {
    let _p: Box<dyn Base> = Box::new(Derived { payload: "x".repeat(100) });
}
