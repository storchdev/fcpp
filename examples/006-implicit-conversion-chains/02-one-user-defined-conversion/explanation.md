# 006.02 — Implicit conversion chains: at most one user-defined conversion

## Why the bad code is wrong (`bad.cpp`)

An implicit conversion sequence ([over.ics.user]) can contain at most one user-defined conversion. `travel(5.0)` would need `double` to `Meters` (converting constructor) and then `Meters` to `Distance` (converting constructor). That is two user-defined conversions, so the sequence does not exist and the call is ill-formed. g++ 16.2 reports `error: could not convert '5.0e+0' from 'double' to 'Distance'`.

The surprise is the asymmetry with nearby code that works:

- `travel(Meters(5.0))` is fine: one user-defined conversion.
- `Distance d(5.0);` and `Distance d{5.0};` (direct-initialization) are also fine; I checked both with g++ 16.2 and clang++ 23.1: the constructor `Distance(Meters)` is a candidate and its *argument* `5.0` gets one user-defined conversion to `Meters`. Direct-initialization is allowed to convert the constructor's argument, whereas copy-initialization (and a function argument) cannot add a second one.
- `Distance d = 5.0;` is an error for the same reason `travel(5.0)` is.

So a type can be constructed from `double` in one spelling and not in another. Adding or removing a constructor in a wrapper layer changes which of them compile, with errors that point at the call site and not at the missing constructor.

## The fix (`good.cpp`)

Decide where the conversion happens and write it down: either a constructor that takes what callers really have (`Distance(double)`), or an explicit conversion at the call site (`Distance(Meters(5.0))`). Marking the constructors `explicit` (see 007) also keeps `double` from becoming a `Meters` or a `Distance` by accident anywhere else.

## Rust (no `good.rs`)

Rust has no implicit user-defined conversions at all: `From`/`Into` are called explicitly, so the chain would have to be written out.
