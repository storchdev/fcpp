// Rust return types are always written out; there is no deduced-return-type decay.
// Returning a reference is spelled `&mut T`, and the borrow checker ties it to the container.
#[derive(Default, Debug)]
struct Cell {
    n: i32,
}

fn at(c: &mut [Cell], i: usize) -> &mut Cell {
    &mut c[i]
}

fn main() {
    let mut cells = vec![Cell::default(), Cell::default()];
    at(&mut cells, 0).n = 5;
    println!("cells[0].n = {}", cells[0].n);
}
