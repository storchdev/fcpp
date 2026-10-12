// `first` ties its result to its argument through lifetime elision. Returning it from a function that owns the
// vector would be E0515 ("returns a value referencing data owned by the current function").
fn load_names() -> Vec<String> {
    vec!["alice-long-enough-to-defeat-sso-0123456789".to_string(), "bob".to_string()]
}

fn first(v: &[String]) -> &String {
    &v[0]
}

// fn default_name() -> &'static String { first(&load_names()) }   // error[E0515]
fn default_name() -> String {
    first(&load_names()).clone()
}

fn main() {
    println!("{}", default_name());
}
