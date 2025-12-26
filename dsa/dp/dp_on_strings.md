# Graphs

## Longest Common Subsequence
- Given two strings, we need to find the longest subsequence (sequence of char is maintained), which is common in both the strings.
- We can have 2 pointers, one for each string, and based on that we can take decision at every index.
- Since, the problem can be divided into sub-problems and there are overlapping sub-problems, hence, we can solve this question using DP.
- Code:
    ```cpp
    // Using Top-Down approach
    class Solution {
        int lcsInternal(int i, int j, int n1, int n2, string& text1, string& text2, vector<vector<int>>& dp) {
            if(dp[i][j] != -1)
                return dp[i][j];
            if(i == n1 || j == n2)
                return dp[i][j] = 0;
            if(text1[i] == text2[j])
                return dp[i][j] = 1 + lcsInternal(i+1, j + 1, n1, n2, text1, text2, dp);
            return dp[i][j] = max(
                lcsInternal(i+1, j, n1, n2, text1, text2, dp),
                lcsInternal(i, j+1, n1, n2, text1, text2, dp)
            );
        }
    public:
        int longestCommonSubsequence(string text1, string text2) {
            int n1 = text1.size(), n2 = text2.size();
            vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, -1));
            return lcsInternal(0, 0, text1.size(), text2.size(), text1, text2, dp);
        }
    };

    // Using Bottom-Up approach
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
        for(int i = 1; i <= n1; ++i)
            for(int j = 1; j <= n2; ++j) {
                if(text1[i-1] == text2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        return dp[n1][n2];
    }

    // Space-saving Bottom-Up approach
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size();
        vector<int> prevDP(n2 + 1, 0), currDP(n2 + 1, 0);
        for(int i = 1; i <= n1; ++i) {
            for(int j = 1; j <= n2; ++j) {
                if(text1[i-1] == text2[j-1])
                    currDP[j] = 1 + prevDP[j-1];
                else
                    currDP[j] = max(prevDP[j], currDP[j-1]);
            }
            for(int j = 1; j <= n2; ++j)
                prevDP[j] = currDP[j];
        }
            
        return prevDP[n2];
    }
    ```
- Time complexity: O(n*m), Space complexity: O(n*m)

### Sample Questions
- [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)
- [Print Longest Common Subsequence](https://www.naukri.com/code360/problems/print-longest-common-subsequence_8416383?leftPanelTabValue=PROBLEM)
- [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/description/)
- [1312. Minimum Insertion Steps to Make a String Palindrome](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/)
- [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/description/)
- []()


## Other Problems
- [72. Edit Distance](https://leetcode.com/problems/edit-distance/description/)
- [44. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/description/)