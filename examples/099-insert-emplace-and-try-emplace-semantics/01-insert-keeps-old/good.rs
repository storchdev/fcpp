// HashMap::insert overwrites and returns the previous value; entry().or_insert keeps the old one. Both are explicit.
use std::collections::HashMap;

fn main() {
    let mut m: HashMap<i32, i32> = HashMap::new();
    m.insert(1, 10);
    let old = m.insert(1, 99);
    println!("m[1] = {}, replaced {:?}", m[&1], old);
    m.entry(1).or_insert(5);
    println!("m[1] = {} after or_insert", m[&1]);
}
