// The fold type must match: starting from an integer 0 with f64 elements is rejected.
fn main() {
    let v = [0.5_f64, 0.5, 0.5, 0.5];
    // let sum = v.iter().fold(0, |a, b| a + b);   // error[E0277]: cannot add `&f64` to `{integer}`
    let sum: f64 = v.iter().sum();
    println!("sum = {}", sum);
}
