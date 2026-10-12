# 143 — `std::async` execution policy surprises

| Case | Surprise |
| --- | --- |
| `01-discarded-future` | With `launch::async` the future's destructor blocks until the task finishes, so ignoring the result makes the call synchronous. |
| `02-deferred-never-ready` | A deferred task runs only in `get()`/`wait()`; polling `wait_for` reports `deferred`, never `ready`. |

