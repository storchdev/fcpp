// Rust has no "decays to a copy" deduction: `let` binds exactly the type of the expression,
// and copying a non-Copy struct is an explicit `.clone()`.
#[derive(Clone, Debug)]
struct Particle {
    x: f64,
}

fn main() {
    let mut ps = vec![Particle { x: 1.0 }, Particle { x: 2.0 }];

    let view = &ps[0]; // &Particle: shared, read-only
    // view.x = 99.0;  // error[E0594]: cannot assign to `view.x`, which is behind a `&` reference
    println!("{}", view.x);

    for p in ps.iter_mut() {
        p.x += 10.0; // p: &mut Particle
    }
    println!("{} {}", ps[0].x, ps[1].x);
}
