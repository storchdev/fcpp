fn main() {
    // let limit = 7;
    // limit = 9; // E0384: cannot assign twice to immutable variable `limit`.
    let mut limit = 7;
    println!("before={limit}");
    limit = 9;
    println!("limit={limit}");
}
