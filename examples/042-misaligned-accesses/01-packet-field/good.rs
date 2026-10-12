// Safe Rust has no pointer casts to unaligned types: build the integer from bytes explicitly.
fn read_len(pkt: &[u8]) -> u32 {
    u32::from_le_bytes([pkt[1], pkt[2], pkt[3], pkt[4]])
}

fn main() {
    let pkt = [0u8, 0x10, 0, 0, 0, 0, 0, 0];
    println!("{}", read_len(&pkt));
}
