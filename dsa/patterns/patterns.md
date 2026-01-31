# DSA Patterns

- Sliding Window (when contiguous subarray required)
    - **Exactly `k`**: Solve using `Atmost(k) - Atmost(k-1)`
    - **Minimum Window / Expand while condition is false, shrink while condition is true**: Add windows possible on right of `r` to the answer on each shrink.
    - **Fixed-size sliding window**: Find state for first window and then keep on incrementing `l` and `r` together to maintain window size.
