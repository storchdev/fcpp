// Rust has no value categories. A by-value parameter is simply owned; passing it on moves it,
// and using it afterwards is E0382. There is no "named rvalue reference that silently copies".
struct Buffer {
    data: String,
}

fn consume_ref(_b: &Buffer) {}
fn consume(b: Buffer) -> usize {
    b.data.len()
}

fn take(b: Buffer) {
    consume_ref(&b);
    let n = consume(b); // moved here
    // consume(b);      // error[E0382]: use of moved value: `b`
    println!("{}", n);
}

fn main() {
    take(Buffer { data: "0123456789012345678901234567890123456789".to_string() });
}
