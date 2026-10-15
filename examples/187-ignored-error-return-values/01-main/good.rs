fn save_config() -> Result<(), &'static str> {
    Err("configuration could not be saved")
}

fn main() {
    match save_config() {
        Ok(()) => println!("configuration saved"),
        Err(message) => println!("{message}"),
    }
}
