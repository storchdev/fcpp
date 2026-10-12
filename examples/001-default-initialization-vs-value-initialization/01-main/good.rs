// Rust has no "default-initialized but indeterminate" state in safe code.
#[derive(Default, Debug)]
struct Point {
    x: i32,
    y: i32,
}

fn main() {
    // let a: i32;
    // println!("{}", a);   // error[E0381]: used binding `a` isn't initialized

    let p = Point::default();               // explicit, zeroed
    let q = Point { x: 1, y: 2 };           // every field must be named
    let buf = vec![0i32; 4];                // zero-filled
    println!("{p:?} {q:?} {}", buf[0]);
}
