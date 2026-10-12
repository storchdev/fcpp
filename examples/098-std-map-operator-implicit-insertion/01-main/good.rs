// HashMap indexing never inserts (a missing key panics); get returns an Option and entry() makes insertion explicit.
use std::collections::HashMap;

fn main() {
    let mut stock: HashMap<&str, i32> = HashMap::new();
    stock.insert("apple", 3);
    println!("size before = {}", stock.len());
    if stock.get("pear").copied().unwrap_or(0) == 0 { println!("pear is out of stock"); }
    println!("size after = {}", stock.len());
    *stock.entry("pear").or_insert(0) += 1;     // insertion only when written explicitly
    println!("size with entry = {}", stock.len());
}
