fn main() {
    let samples = [10, 20, 30];
    let index = samples.len();
    match samples.get(index) {
        Some(value) => println!("{value}"),
        None => println!("invalid sample index"),
    }
}
