# 064.01 — Unsequenced side effects: two increments of one variable

## Why the bad code is wrong (`bad.cpp`)

If a side effect on a scalar object is unsequenced relative to another side effect on the same object, or to a value computation that uses the object, the behavior is undefined. The two operands of `+` are unsequenced with respect to each other (C++17 added ordering rules for assignment, `<<`, `>>`, `&&`, `||` and `,`, but not for the operands of arithmetic operators). So `i++ + ++i` modifies `i` twice with nothing ordering the two modifications: UB, not merely "unspecified order".

The program printed `r = 4, i = 3` with both compilers at `-O0` and `-O2`. That looks like a stable answer, but the standard promises nothing: the compiler may assume the program does not do this, and a different version or optimization setting is free to produce another value or something else entirely. An answer that is the same on two compilers is not evidence of defined behavior.

Both compilers warn under `-Wall -Wextra`: g++ `-Wsequence-point` ("operation on ‘i’ may be undefined"), clang++ `-Wunsequenced` ("multiple unsequenced modifications to 'i'"). When I ran it with `-fsanitize=undefined,address` neither compiler's sanitizer reported anything, so the warning is the main detection.

## The fix (`good.cpp`)

Perform one side effect per full-expression: separate statements each have a sequence point at the semicolon. Write what you mean (`first = i++; second = ++i;`) and only then combine.

## Rust (no `good.rs`)

No Rust equivalent is provided for this case.
