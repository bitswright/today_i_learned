# [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/description/)
Find the length of longest substring of consecutive 1's in a binary string if `k` 0's can be flipped.

## Solutions:
### Brute Force: 
- Idea:
    - Generate all substrings $O(n^2)$
    - Count number of zeros in substrings. $O(n)$
    - Keep track of longest substring with maximum `k` zeros.
- TC: $O(n^3)$
- SC: $O(1)$
### Optimizing using Prefix-Sum
- Idea:
    - Calculate prefix-sum array for the given array. $O(n)$
    - Keep track of substring using a window.
    - Expand the window on the right and shrink the window from the left while keeping the following condition true $O(n)$: 
        ```
        prefixSum[r] - prefixSum[l] <= j - i - k
        ```
    - Keep track of longest substring with maximum `k` zeros.

