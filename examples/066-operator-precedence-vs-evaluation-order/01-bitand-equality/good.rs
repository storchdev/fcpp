// In Rust `&` binds tighter than `==`, the opposite of C++.
fn main() {
    let flags: u32 = 0x1;
    const MASK: u32 = 0x4;
    // `flags & MASK == 0` parses as `(flags & MASK) == 0`; the parentheses below are just for the reader.
    if flags & MASK == 0 {
        println!("bit 2 is clear");
    } else {
        println!("bit 2 is set");
    }
}
