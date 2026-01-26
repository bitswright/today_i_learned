# [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
Find the length of longest substring without repeating characters.

## Solutions:
- Brute Force: 
    - Idea:
        - Generate all substrings $O(n^2)$, 
        - For each substring, check if it has duplicate characters $O(n)$,
        - Keep track of maximum length.
    - TC: $O(n^3)$
    - SC: $O(1)$ (instead of set, we can you an array of length 26/52/256).
- Slight Improvement:
    - Idea: 
        - Instead of generating all substrings, starting from each index `0` to `n-1`, keep on moving forward till a duplicate character appears,
        - Keep track of maximum length.
    - TC: $O(n^2)$
    - SC: $O(1)$
- Using Sliding Window:
    - Idea:
        - Use two pointers `l` and `r` representing a window. 
        - Window contains only unique characters. 
        - Expand from right and if duplicate found shrink from left.
    - TC: $O(2n) = $O(n)$
    - SC: $O(1)$
    - Code:
        ```cpp
        int lengthOfLongestSubstring(string s) {
            int n = s.length();
            int l = 0, r = 0;
            int isPresent[256] = {0};
            int maxSubStrLen = 0;
            while(r < n) {
                while(isPresent[s[r]]) {
                    isPresent[s[l]] = 0;
                    l++;
                }
                isPresent[s[r]] = 1;
                r++;
                maxSubStrLen = max(maxSubStrLen, r - l);
            }
            return maxSubStrLen;
        }
        ```
- Using Sliding Window with jumping:
    - Idea:
        - Use two pointers `l` and `r` representing a window. 
        - Window contains only unique characters. 
        - Expand from right and if duplicate found jump `l` to the last index of the character at consideration on right.
    - Code:
        ```cpp
        int lengthOfLongestSubstring(string s) {
            int n = s.length();
            int l = 0, r = 0;
            vector<int> lastIndex(256, -1);
            int maxSubStrLen = 0;
            while(r < n) {
                l = max(l, lastIndex[s[r]] + 1);
                lastIndex[s[r]] = r;
                r++;
                maxSubStrLen = max(maxSubStrLen, r - l);
            }
            return maxSubStrLen;
        }
        ```