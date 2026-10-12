// std::cmp::max takes and returns values, so there is no reference to a temporary to dangle.
fn main() {
    let longest = std::cmp::max(String::from("apple"), String::from("banana"));
    println!("{}", longest);
}
