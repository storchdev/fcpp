// Rust makes the failure path explicit with Option/Result; there is no out-parameter to forget.
fn parse_port(text: &str) -> Option<i32> {
    text.parse().ok()
}

fn main() {
    let arg = std::env::args().nth(1).unwrap_or_else(|| "not-a-number".to_string());
    // let port: i32;                      // reading it before every path assigns it is error[E0381]
    let port = parse_port(&arg).unwrap_or(8080);
    println!("port = {}", port);
}
