// Box<[T]>, Vec<T> and Box<T> each know how to free themselves; there is no delete/delete[] choice.
fn main() {
    let values: Box<[i32]> = vec![1, 2, 3, 4].into_boxed_slice();
    println!("{}", values[3]);
}
