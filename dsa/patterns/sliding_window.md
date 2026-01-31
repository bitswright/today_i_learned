# Sliding Window Pattern

## When to think Sliding Window
Use this pattern when you see:
- **Contiguous subarray / substring**
- Words like:
  - longest / shortest
  - maximum / minimum
  - count of subarrays
- Constraints like:
  - at most K
  - exactly K
  - replace / flip / change limited times

If the problem says *subsequence* → usually NOT sliding window.

## Core intuition
- Window represents a **range [l, r]**
- Expand `r` to explore
- Shrink `l` only when window becomes invalid
- Maintain some state (count, sum, freq, max)
> “Grow greedily, shrink only to restore validity”

## Standard template

```cpp
int l = 0;
for (int r = 0; r < n; r++) {
    add(nums[r]);           // include right element

    while (window_invalid()) {
        remove(nums[l]);    // remove left element
        l++;
    }

    update_answer(r - l + 1);
}
```

## Common window states
Depending on problem, track:
- Frequency map (characters, numbers)
- Count of distinct elements
- Sum of window
- maxFreq (sometimes allowed to be stale)

## Classic problems
- Exactly K trick
  - [Count Number of Nice Subarrays](/dsa/problems/sliding_window/lc_1248.md)
  - [Subarrays with K Different Integers](/dsa/problems/sliding_window/lc_992.md))
- Minimum Window / Expand while condition is false, shrink while condition is true
  - [Number of Substrings Containing All Three Characters](/dsa/problems/sliding_window/lc_1358.md)
  - [Minimum Window Substring](/dsa/problems/sliding_window/lc_76.md)
- Fixed-size sliding window
  - [Maximum Points You Can Obtain from Cards](/dsa/problems/sliding_window/lc_1423.md)

## Important variations
1. At most K
    - Sliding window works directly
    - Shrink when count > K
2. Exactly K
- Often solved as: `atMost(K) - atMost(K-1)`


## Mental checklist before coding
Ask yourself:
- Is the data contiguous?
- What makes the window invalid?
- What do I track to detect invalidity?
- When exactly should `l` move?

## One-line recall
**“Expand right greedily, shrink left only to restore validity.”**
