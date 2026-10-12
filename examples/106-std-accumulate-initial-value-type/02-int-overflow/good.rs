// Overflow is explicit: checked_add returns None, and widening first avoids it.
fn main() {
    let v = [i32::MAX, 1];
    let narrow = v.iter().try_fold(0i32, |a, &b| a.checked_add(b));
    let wide: i64 = v.iter().map(|&x| i64::from(x)).sum();
    println!("checked i32 sum = {:?}, i64 sum = {}", narrow, wide);
}
