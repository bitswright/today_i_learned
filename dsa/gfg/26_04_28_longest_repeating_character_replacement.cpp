/*
Given a string s of length n consisting of uppercase English letters and an integer k, you are allowed to perform at most k operations.  In each operation, you can change any character of the string to any other uppercase English letter.

Determine the length of the longest substring that can be transformed into a string with all identical characters after performing at most k such operations.

Examples:
    Input: s = "ABBA", k = 2 
    Output: 4 
    Explanation: The string "ABBA" can be fully converted into the same character using at most 2 changes. By replacing both 'A' with 'B', it becomes "BBBB". Hence, the maximum length is 4.
    
    Input: s = "ADBD", k = 1
    Output: 3
    Explanation: In the string "ADBD", we can make at most 1 change. By changing 'B' to 'D', the string becomes "ADDD", which contains a substring "DDD" of length 3.

Constraints:
    1 ≤ n, k ≤ 10^5
    s consists of only uppercase English letters.

Time Complexity: O(n)
Auxiliary Space: O(1)
*/

// BRUTE FORCE APPROACH
/*
For each substring of the given array, find the frequency of the longest repeating character (say f).
If f + k >= length of substring, then we can make all characters in the substring same. Hence, we update the maximum length based on current substring length.
Else we move to the next substring.

To save time complexity, we can create substrings by using two pointers (l and r). We keep on increasing l one by one till n-1. And for each l, increament r till n.
Whenever r is moved ahead, update freq of the current character at r and update maxFreq character.
For each l, reset the frequency array and maxFreq.
*/

// USING TWO-POINTER APPROACH
/*
We can use two pointers to create substrings. We keep on increasing r one by one till n-1. And for each r, we update the frequency of the current character at r and update maxFreq character.
Whenever r is moved ahead, we also need to check if we can form a valid substring by using at most k operations.
If the current window size minus maxFreq is greater than k, we need to move the left pointer l to the right while updating the frequency of the character at l until we have a valid window again.
*/

int longestSubstr(string& s, int k) {
    int freq[26] = {0};
    int maxFreq = 0;
    int n = s.length();
    int l = 0, r = 0;
    int maxLength = 0;
    while(r < n) {
        freq[s[r] - 'A']++;
        if(freq[s[r] - 'A'] > maxFreq)
            maxFreq = freq[s[r] - 'A'];
        r++;
        while((r - l) - maxFreq > k) {
            freq[s[l] - 'A']--;
            l++;
        }
        if((r - l) > maxLength) {
            maxLength = r - l;
        }
    }
    
    return maxLength;
}