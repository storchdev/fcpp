// A struct holding a reference carries a lifetime parameter, so the borrow checker ties it to the referent.
struct Logger<'a> {
    prefix: &'a str,
}

impl<'a> Logger<'a> {
    fn new(prefix: &'a str) -> Self {
        Logger { prefix }
    }
    fn log(&self, msg: &str) {
        println!("[{}] {}", self.prefix, msg);
    }
}

fn main() {
    let prefix = String::from("a-long-enough-prefix-to-defeat-small-string-opt");
    let logger = Logger::new(&prefix);
    logger.log("started");
    // let bad = Logger::new(&String::from("tmp"));
    // bad.log("x");  // error[E0716]: temporary value dropped while borrowed
}
