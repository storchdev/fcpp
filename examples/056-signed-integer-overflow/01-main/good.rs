// Rust makes you choose the overflow behavior explicitly.
fn main() {
    let x = i32::MAX;

    println!("checked:    {:?}", x.checked_add(1));      // None
    println!("wrapping:   {}", x.wrapping_add(1));       // -2147483648
    println!("saturating: {}", x.saturating_add(1));     // 2147483647
    println!("overflowing: {:?}", x.overflowing_add(1)); // (-2147483648, true)

    // Plain `x + 1` panics in debug builds and wraps in release (never UB).
}
