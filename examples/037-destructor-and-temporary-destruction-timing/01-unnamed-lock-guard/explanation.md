# 037.01 — Destructor and temporary destruction timing: the unnamed lock guard

## Why the bad code is wrong (`bad.cpp`)

`std::lock_guard<std::mutex>{m};` constructs a temporary, which locks `m`, and destroys it at the end of that full-expression, which unlocks `m`. The guard exists only for the length of the statement that created it, so `++counter;` runs with the mutex unlocked. Two threads execute that increment concurrently: a data race, undefined behavior. ThreadSanitizer reports `WARNING: ThreadSanitizer: data race` on g++ 16.2.1 and clang++ 23.1.1 (`-std=c++17 -fsanitize=thread -O1`); I have not claimed a specific wrong total, since the result depends on scheduling. (The named version prints `counter = 2000`.)

The statement looks like a normal RAII guard with the variable name forgotten. Both compilers warn under `-Wall -Wextra` because `lock_guard`'s constructor is `[[nodiscard]]`: g++ `warning: ignoring return value of ‘std::lock_guard<_Mutex>::lock_guard(mutex_type&)’ … [-Wunused-result]`, clang++ `warning: ignoring temporary created by a constructor declared with 'nodiscard' attribute [-Wunused-value]`. clang-tidy `bugprone-unused-raii` reports `object destroyed immediately after creation; did you mean to name the object?`.

The variant `std::lock_guard<std::mutex>(m);` (parentheses, no braces) is different: it parses as a declaration of a variable named `m`. In a scratch program g++ warned `unnecessary parentheses in declaration of ‘m’ [-Wparentheses]` and then failed with `no matching function for call to ‘std::lock_guard<std::mutex>::lock_guard()’`; clang++ warned `parentheses were disambiguated as redundant parentheses around declaration of variable named 'm' [-Wvexing-parse]`.

## The fix (`good.cpp`)

Give the guard a name: `std::lock_guard<std::mutex> lock(m);`. It then lives to the end of the block. `std::scoped_lock lock(m);` (C++17, compiled in a scratch program on both compilers) does the same with class template argument deduction.

## Rust (`good.rs`)

The Rust `Mutex<T>` owns the data and exposes it only through a guard, so the counter cannot be touched without holding the lock. (A guard created in `*counter.lock().unwrap() += 1;` is also a temporary, but it lives for the whole statement that uses the data.)
