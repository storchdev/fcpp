// `sort` on f64 does not compile (f64 is not Ord); total_cmp is an explicit total order that places NaN.
fn main() {
    let nan = f64::NAN;
    let mut v = vec![5.0, 3.0, nan, 8.0, 1.0, nan, 9.0, 2.0, 7.0, 4.0, 6.0, 0.0];

    // v.sort();   // error[E0277]: the trait bound `f64: Ord` is not satisfied

    v.sort_by(f64::total_cmp);
    println!("{:?}", v); // numbers ascending, then NaN
}
