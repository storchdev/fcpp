// Slice operations are bounds-checked: copy_from_slice panics on a length mismatch instead of writing out of bounds.
fn main() {
    let src = [1, 2, 3, 4];
    let mut dst = [0; 2];
    // dst.copy_from_slice(&src);   // panics: copy_from_slice: source slice length (4) does not match destination slice length (2)
    let mut grown = Vec::new();
    grown.extend_from_slice(&src);
    dst.copy_from_slice(&src[..2]);
    println!("dst = {:?}, grown.len() = {}", dst, grown.len());
}
