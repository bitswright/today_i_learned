/*
You are given an array arr[], in which arr[i] is the price of a given stock on the ith day and an integer k represents a transaction fee. Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Examples:
    Input: arr[] = [6, 1, 7, 2, 8, 4], k = 2
    Output: 8
    Explanation:
    Buy the stock on day 2 and sell it on day 3 => 7 – 1 -2 = 4
    Buy the stock on day 4 and sell it on day 5 => 8 – 2 - 2 = 4
    Maximum Profit  = 4 + 4 = 8

    Input: arr[] = [7, 1, 5, 3, 6, 4], k = 1
    Output: 5
    Explanation: 
    Buy the stock on day 2 and sell it on day 3 => 5 – 1 - 1 = 3
    Buy the stock on day 4 and sell it on day 5 => 6 – 3 - 1 = 2
    Maximum Profit  = 3 + 2 = 5


Constraint:
    1 ≤ arr.size() ≤ 10^6
    1 ≤ arr[i] ≤ 10^6
    0 ≤ k ≤ 10^6
*/

// Using Top-Down DP Approach: TC: O(n), SC:O(n)
class Solution {
    int maxProfit(int i, int buy, int n, vector<int>& arr, int k, vector<vector<int>>& dp) {
        if(i == n)
            return 0;
        if(dp[i][buy] != -1)
            return dp[i][buy];
        
        if(buy) {
            return dp[i][buy] = max(
                -arr[i] + maxProfit(i+1, 0, n, arr, k, dp),
                maxProfit(i+1, 1, n, arr, k, dp)
            );
        } else { 
            // sell
            return dp[i][buy] = max(
                arr[i] + maxProfit(i+1, 1, n, arr, k, dp) - k,
                maxProfit(i+1, 0, n, arr, k, dp)
            );
            
        }
    }
    
  public:
    int maxProfit(vector<int>& arr, int k) {
        // Code here
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(2, -1)); 
        return maxProfit(0, 1, n, arr, k, dp);
    }
};

// Using Bottom-Up DP Approach: TC: O(n), SC:O(n)
class Solution {
  public:
    int maxProfit(vector<int>& arr, int k) {
        // Code here
        int n = arr.size();
        vector<vector<int>> dp(n+1, vector<int>(2)); 
        dp[n][0] = 0;
        dp[n][1] = 0;
        for(int i = n-1; i >= 0; --i) {
            dp[i][0] = max(arr[i] + dp[i+1][1] - k, dp[i+1][0]);
            dp[i][1] = max(-arr[i] + dp[i+1][0], dp[i+1][1]);
        }
        return dp[0][1];
    }
};