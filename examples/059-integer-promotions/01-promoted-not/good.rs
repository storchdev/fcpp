// Rust never promotes: u8 arithmetic stays u8, and `!` on a u8 is a u8.
fn main() {
    let mask: u8 = 0x0F;
    println!("!mask == 0xF0: {}", !mask == 0xF0);

    let a: u8 = 200;
    let b: u8 = 100;
    println!("checked: {:?}", a.checked_add(b)); // None: 300 does not fit
    println!("wrapping: {}", a.wrapping_add(b)); // 44
    println!("widened: {}", u16::from(a) + u16::from(b)); // 300
}
