// Rust multiplies u16 as u16; widening is an explicit choice.
fn main() {
    let a: u16 = 65535;
    let b: u16 = 65535;
    println!("{}", u32::from(a) * u32::from(b)); // 4294836225
    println!("{:?}", a.checked_mul(b));           // None
}
