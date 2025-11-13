// Wildcard Pattern Matching

/*
Given two strings pat and txt which may be of different sizes, You have to return true if the wildcard pattern i.e. pat, matches with txt else return false.

The wildcard pattern pat can include the characters '?' and '*'.

'?' – matches any single character.
'*' – matches any sequence of characters (including the empty sequence).
Note: The matching should cover the entire txt (not partial txt).

Examples :
Input: txt = "abcde", pat = "a?c*"
Output: true
Explanation: '?' matches with 'b' and '*' matches with "de".

Input: txt = "baaabab", pat = "a*ab"
Output: false
Explanation: The pattern starts with a, but the text starts with b, so the pattern does not match the text.

Input: txt = "abc", pat = "*"
Output: true
Explanation: '*' matches with whole text "abc".

Constraints:
1 ≤ txt.size(), pat.size() ≤ 100

Expected Complexities
Time Complexity: O(n * m)
Auxiliary Space: O(n * m)
*/

/*
Solution:
By first glance we can think of using recursion to solve this problem.
But the recursive approach would lead to overlapping subproblems.
Hence, we can use Dynamic Programming to solve this problem.
*/

// Brute Force Approach (Using Recursion): O(2^(m*n))
class Solution {
  public:
    bool wildCardInternal(int i, int j, int tl, int pl, string& txt, string& pat) {
        if(i == tl) {
            while(j < pl) {
                if(pat[j] == '*')
                    j++;
                else
                    return false;
            }
            return true;
        }
        if(j == pl)
            return false;
        if(txt[i] == pat[j])
            return wildCardInternal(i+1, j+1, tl, pl, txt, pat);
        if(pat[j] == '?')
            return wildCardInternal(i+1, j+1, tl, pl, txt, pat);
        if(pat[j] == '*') {
            bool useStarAsEmptyString = wildCardInternal(i, j+1, tl, pl, txt, pat);
            bool useStarForCurrChar = wildCardInternal(i+1, j, tl, pl, txt, pat);
            return useStarAsEmptyString || useStarForCurrChar;
        }
        return false;
    }
    
    bool wildCard(string &txt, string &pat) {
        int tl = txt.size(), pl = pat.size();
        return wildCardInternal(0, 0, txt.size(), pat.size(), txt, pat);
    }
};

// Optimal Approach using Dynamic Programming (Top-Down DP): O(n*m)
class Solution {
  public:
    bool wildCardInternal(int i, int j, int tl, int pl, string& txt, string& pat, vector<vector<int>>& dp) {
        if(dp[i][j] != -1)
            return dp[i][j];
        if(i == tl) {
            while(j < pl) {
                if(pat[j] == '*')
                    j++;
                else
                    return dp[i][j] = false;
            }
            return dp[i][j] = true;
        }
        if(j == pl)
            return dp[i][j] = false;
        if(txt[i] == pat[j])
            return dp[i][j] = wildCardInternal(i+1, j+1, tl, pl, txt, pat, dp);
        if(pat[j] == '?')
            return dp[i][j] = wildCardInternal(i+1, j+1, tl, pl, txt, pat, dp);
        if(pat[j] == '*') {
            bool useStarAsEmptyString = wildCardInternal(i, j+1, tl, pl, txt, pat, dp);
            bool useStarForCurrChar = wildCardInternal(i+1, j, tl, pl, txt, pat, dp);
            return dp[i][j] = useStarAsEmptyString || useStarForCurrChar;
        }
        return false;
    }
    
    bool wildCard(string &txt, string &pat) {
        int tl = txt.size(), pl = pat.size();
        vector<vector<int>> dp(tl + 1, vector<int>(pl + 1, -1));
        return wildCardInternal(0, 0, txt.size(), pat.size(), txt, pat, dp);
    }
};

// Optimal Approach using Dynamic Programming (Bottom-Up DP): O(n*m)
bool wildCard(string &txt, string &pat) {
        int tl = txt.size(), pl = pat.size();
        vector<vector<bool>> dp(tl + 1, vector<bool>(pl + 1, false));
        dp[0][0] = true;
        int j = 0;
        while(j < pl && pat[j] == '*') {
            dp[0][j+1] = true;
            j++;
        }
        for(int i = 1; i <= tl; ++i)
            for(int j = 1; j <= pl; ++j) {
                if(txt[i-1] == pat[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else if(pat[j-1] == '?')
                    dp[i][j] = dp[i-1][j-1];
                else if(pat[j-1] == '*')
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        return dp[tl][pl];
    }