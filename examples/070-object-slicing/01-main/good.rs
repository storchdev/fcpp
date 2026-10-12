// Rust has no inheritance; a trait object is always behind a pointer, so there is nothing to slice.
trait Shape {
    fn name(&self) -> &'static str { "Shape" }
}
struct Circle;
impl Shape for Circle {
    fn name(&self) -> &'static str { "Circle" }
}

fn describe(s: &dyn Shape) { println!("by reference: {}", s.name()); }

fn main() {
    let c = Circle;
    describe(&c);
    let shapes: Vec<Box<dyn Shape>> = vec![Box::new(Circle)];
    println!("in vector: {}", shapes[0].name());

    // fn by_value(s: dyn Shape) {}   // error[E0277]: the size for values of type `dyn Shape` cannot be known
}
