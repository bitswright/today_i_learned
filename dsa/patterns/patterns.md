# DSA Patterns

- Sliding Window (when contiguous subarray required)
    - **Exactly `k`**: Solve using `Atmost(k) - Atmost(k-1)`
    - **Expand while condition is false, shrink while condition is true**: Add windows possible on right of `r` to the answer on each shrink.
