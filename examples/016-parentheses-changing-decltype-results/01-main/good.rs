// Rust has no decltype; a binding is a copy (for Copy types) or a reference only if you write `&`.
struct Config {
    limit: i32,
}

fn main() {
    let mut cfg = Config { limit: 10 };
    let before = cfg.limit; // copy of an i32
    cfg.limit = 99;
    println!("before = {}, limit = {}", before, cfg.limit); // before = 10, limit = 99
}
