// Rust struct literals always name their fields, in any order, and must supply every field.
struct Window {
    border: i32,
    height: i32,
    width: i32,
}

fn main() {
    // let w = Window { 800, 600, 2 };                      // error: expected identifier, found `800` (no positional form)
    // let w = Window { width: 800, height: 600 };          // error[E0063]: missing field `border` in initializer of `Window`
    let w = Window { width: 800, height: 600, border: 2 };  // order is irrelevant
    println!("{}x{} border={}", w.width, w.height, w.border);
}
