// Safe Rust offers `to_bits` / `from_bits`; reading a union field requires `unsafe` and a valid bit pattern.
fn main() {
    let u = 1.0f32.to_bits();
    println!("{:08x}", u);
}
