// f64 is only PartialOrd, so it cannot be a BTreeMap key without a decision about NaN.
fn main() {
    let nan = f64::NAN;
    println!("nan == nan: {}", nan == nan);            // false
    println!("nan < 1.0: {}, nan > 1.0: {}", nan < 1.0, nan > 1.0); // false, false

    // let mut m = std::collections::BTreeMap::new(); m.insert(nan, 1);   // error[E0277]: the trait bound `f64: Ord` is not satisfied

    // Wrap the value in a type whose Ord you choose, or reject NaN up front:
    let key = if nan.is_nan() { None } else { Some(nan) };
    println!("key: {:?}", key);
}
