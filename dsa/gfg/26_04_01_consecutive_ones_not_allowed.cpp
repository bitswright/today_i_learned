/*
Given a positive integer n, count all possible distinct binary strings of length n such that there are no consecutive 1’s.

Examples :
    Input: n = 3
    Output: 5
    Explanation: 5 strings are ("000", "001", "010", "100", "101").

    Input: n = 2
    Output: 3
    Explanation: 3 strings are ("00", "01", "10").

    Input: n = 1
    Output: 2

Constraints:
    1 ≤ n ≤ 44

Time Complexity: O(n)
Auxiliary Space: O(n)
*/

class Solution {
    int countStrings(int n, int bit, vector<vector<int>>& dp) {
        if(dp[n][bit] != -1)
            return dp[n][bit];
        if(n == 0)
            return dp[n][bit] = 1;
        if(bit == 1)
            return dp[n][bit] = countStrings(n-1, 0, dp);
        return dp[n][bit] = countStrings(n-1, 0, dp) + countStrings(n-1, 1, dp);
    }
  public:
    int countStrings(int n) {
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return countStrings(n-1, 0, dp) + countStrings(n-1, 1, dp);
    }
};
