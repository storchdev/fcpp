// Rc::new takes ownership of the value, so there is no raw pointer to build a second owner from.
use std::rc::Rc;

struct Widget { id: i32 }
impl Drop for Widget { fn drop(&mut self) { println!("drop Widget {}", self.id); } }

fn main() {
    let w = Box::new(Widget { id: 1 });
    let a: Rc<Widget> = Rc::from(w);
    // let b: Rc<Widget> = Rc::from(w);   // error[E0382]: use of moved value: `w`
    let b = Rc::clone(&a);
    println!("strong_count a={} b={}", Rc::strong_count(&a), Rc::strong_count(&b));
}
