enum Charge {
    Base,
    Bonus,
}

fn price(charge: Charge) -> i32 {
    match charge {
        Charge::Base => 10,
        Charge::Bonus => 2,
    }
}

fn main() {
    let _ = Charge::Bonus;
    println!("{}", price(Charge::Base));
}
