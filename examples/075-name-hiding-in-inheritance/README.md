# 075 — Name hiding in inheritance

| Case | Mistake |
| --- | --- |
| `01-hidden-overload` | A derived-class function of the same name hides all base overloads, so a call that would match a base overload fails to compile. |
| `02-silent-wrong-overload` | The hiding function accepts the argument through a conversion, so the call compiles and runs the wrong function. |
