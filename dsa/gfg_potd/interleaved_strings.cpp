// Interleaved Strings

/*
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
Interleaving of two strings s1 and s2 is a way to mix their characters to form a new string s3, while maintaining the relative order of characters from s1 and s2. Conditions for interleaving:

Characters from s1 must appear in the same order in s3 as they are in s1.
Characters from s2 must appear in the same order in s3 as they are in s2.
The length of s3 must be equal to the combined length of s1 and s2.

Examples :
Input: s1 = "AAB", s2 = "AAC", s3 = "AAAABC", 
Output: true
Explanation: The string "AAAABC" has all characters of the other two strings and in the same order.

Input: s1 = "AB", s2 = "C", s3 = "ACB", 
Output: true
Explanation: s3 has all characters of s1 and s2 and retains order of characters of s1.

Input: s1 = "YX", s2 = "X", s3 = "XXY"
Output: false
Explanation: "XXY " is not interleaved of "YX" and "X". The strings that can be formed are YXX and XYX

Constraints:
1 ≤ s1.length, s2.length ≤ 300
1 ≤ s3.length ≤ 600

Expected Complexities
Time Complexity: O(n * m)
Auxiliary Space: O(m)   
*/

/*
Solution:
By first glance we can think of using recursion to solve this problem.
But the recursive approach would lead to overlapping subproblems.
Hence, we can use Dynamic Programming to solve this problem.

Important points to note:
We just need a 2D DP to solve this problem and not a 3D DP.
Because the length of s3 is always equal to the combined length of s1 and s2.
So, at any point, if we know how many characters we have taken from s1, and s2, 
we can easily find how many characters we have taken from s3.
*/

// Brute Force Approach: O(2^(m*n))
class Solution {
  public:
    bool isInterleaveInternal(int i, int j, int l1, int l2, string& s1, string& s2, string& s3) {
        if(i == l1) {
            if(j == l2)
                return true;
            if(s2[j] == s3[i+j])
                return isInterleaveInternal(i, j + 1, l1, l2, s1, s2, s3);
            return false;
        }
        if(j == l2) {
            if(s1[i] == s3[i+j])
                return isInterleaveInternal(i + 1, j, l1, l2, s1, s2, s3);
            return false;
        }
        if(s1[i] == s2[j]) {
            if(s1[i] == s3[i+j]) {
                bool takeFromS1 = isInterleaveInternal(i + 1, j, l1, l2, s1, s2, s3);
                bool takeFromS2 = isInterleaveInternal(i, j + 1, l1, l2, s1, s2, s3);
                return takeFromS1 || takeFromS2;
            }
            return false;
        }
        if(s1[i] == s3[i+j]) 
            return isInterleaveInternal(i + 1, j, l1, l2, s1, s2, s3);
        if(s2[j] == s3[i+j])
            return isInterleaveInternal(i, j + 1, l1, l2, s1, s2, s3);
        return false;
    }
    
    bool isInterleave(string &s1, string &s2, string &s3) {
        int l1 = s1.size(), l2 = s2.size(), l3 = s3.size();
        if(l1 + l2 != l3)
            return false;
        return isInterleaveInternal(0, 0, l1, l2, s1, s2, s3);
    }
};

// Optimal Approach using Dynamic Programming (Top-Down DP): O(n*m)
class Solution {
  public:
    bool isInterleaveInternal(int i, int j, int l1, int l2, string& s1, string& s2, string& s3, vector<vector<int>>& dp) {
        if(dp[i][j] != -1)
            return dp[i][j];
        if(i == l1) {
            if(j == l2)
                return dp[i][j] = true;
            if(s2[j] == s3[i+j])
                return dp[i][j] = isInterleaveInternal(i, j + 1, l1, l2, s1, s2, s3, dp);
            return dp[i][j] =  false;
        }
        if(j == l2) {
            if(s1[i] == s3[i+j])
                return dp[i][j] = isInterleaveInternal(i + 1, j, l1, l2, s1, s2, s3, dp);
            return dp[i][j] =  false;
        }
        if(s1[i] == s2[j]) {
            if(s1[i] == s3[i+j])
                return dp[i][j] =
                    isInterleaveInternal(i + 1, j, l1, l2, s1, s2, s3, dp) || 
                    isInterleaveInternal(i, j + 1, l1, l2, s1, s2, s3, dp);
            return dp[i][j] = false;
        }
        if(s1[i] == s3[i+j]) 
            return dp[i][j] = isInterleaveInternal(i + 1, j, l1, l2, s1, s2, s3, dp);
        if(s2[j] == s3[i+j])
            return dp[i][j] = isInterleaveInternal(i, j + 1, l1, l2, s1, s2, s3, dp);
        return dp[i][j] =  false;
    }
    
    bool isInterleave(string &s1, string &s2, string &s3) {
        int l1 = s1.size(), l2 = s2.size(), l3 = s3.size();
        if(l1 + l2 != l3)
            return false;
        vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, -1));
        return isInterleaveInternal(0, 0, l1, l2, s1, s2, s3, dp);
    }
};

// Optimal Approach using Dynamic Programming (Bottom-Up DP): O(n*m)
class Solution {
  public:
    bool isInterleave(string &s1, string &s2, string &s3) {
        int l1 = s1.size(), l2 = s2.size(), l3 = s3.size();
        if(l1 + l2 != l3)
            return false;
        vector<vector<bool>> dp(l1 + 1, vector<bool>(l2 + 1, false));
        dp[0][0] = true;
        for(int i = 1; i <= l1; ++i)
            if(s1[i-1] == s3[i-1])
                dp[i][0] = true;
            else
                break;
        for(int j = 1; j <= l2; ++j)
            if(s2[j-1] == s3[j-1])
                dp[0][j] = true;
            else
                break;
        for(int i = 1; i <= l1; ++i)
            for(int j = 1; j <= l2; ++j) {
                if(s1[i-1] == s2[j-1]) {
                    if(s1[i-1] == s3[i+j-1]) 
                        dp[i][j] = dp[i-1][j] || dp[i][j-1];
                    else
                        dp[i][j] = false;
                }
                else if(s1[i-1] == s3[i+j-1]) 
                    dp[i][j] = dp[i-1][j];
                else if(s2[j-1] == s3[i+j-1])
                    dp[i][j] = dp[i][j-1];
                else
                    dp[i][j] = false;
            }
        return dp[l1][l2];
    }
};
