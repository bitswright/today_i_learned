/*
Given an array arr[] and an integer diff, count the number of ways to partition the array into two subsets such that the difference between their sums is equal to diff.
Note: A partition in the array means dividing an array into two subsets say S1 and S2 such that the union of S1 and S2 is equal to the original array and each element is present in only one of the subsets.


Examples :
    Input: arr[] = [5, 2, 6, 4], diff = 3
    Output: 1
    Explanation: There is only one possible partition of this array. Partition : [6, 4], [5, 2]. The subset difference between subset sum is: (6 + 4) - (5 + 2) = 3.

    Input: arr[] = [1, 1, 1, 1], diff = 0 
    Output: 6 
    Explanation: We can choose two 1's from indices [0,1], [0,2], [0,3], [1,2], [1,3], [2,3] and put them in sum1 and remaning two 1's in sum2.
    Thus there are total 6 ways for partition the array arr. 
    
    Input: arr[] = [3, 2, 7, 1], diff = 4  
    Output: 0
    Explanation: There is no possible partition of the array that satisfy the given difference. 

Constraint:
    1 ≤ arr.size() ≤ 50
    0 ≤ diff ≤ 50
    0 ≤ arr[i] ≤ 6

Time Complexity: O(n*sum(arr))
Auxiliary Space: O(sum(arr))
*/

// Using recursion: TC: O(2^n)
class Solution {
  public:
    int get_no_of_ways_to_for_sum(int i, int sumReq, int n, vector<int>& arr) {
        if(i == n) {
            if(sumReq == 0)
                return 1;
            return 0;
        }
        int take = sumReq >= arr[i] ? get_no_of_ways_to_for_sum(i+1, sumReq - arr[i], n, arr) : 0;
        int not_take = get_no_of_ways_to_for_sum(i+1, sumReq, n, arr);
        return take + not_take;
    }
    
    int countPartitions(vector<int>& arr, int diff) {
        // Formula:
        /*
        Pre-requisite:
            a - b = diff
            a + b = total
            2a = total + diff
            a = (total + diff)/2
        */
        
        // Hence, we need to find number of ways we can get a subset of sum (total + diff)/2 
        // total combinations -> 2^n
        int total = accumulate(arr.begin(), arr.end(), 0);
        if((total + diff) % 2)
            return 0;
        return get_no_of_ways_to_for_sum(0, (total + diff)/2, arr.size(), arr);
    }
};

// Using DP: Top-down Approach: TC: O(n*sum(arr)) SC: O(n*sum(arr))
class Solution {
  public:
    int get_no_of_ways_to_for_sum(int i, int sumReq, int n, vector<int>& arr, vector<vector<int>>& dp) {
        if(dp[i][sumReq] != -1)
            return dp[i][sumReq];
        if(i == n) {
            if(sumReq == 0)
                return dp[i][sumReq] = 1;
            return dp[i][sumReq] = 0;
        }
        int take = sumReq >= arr[i] ? get_no_of_ways_to_for_sum(i+1, sumReq - arr[i], n, arr, dp) : 0;
        int not_take = get_no_of_ways_to_for_sum(i+1, sumReq, n, arr, dp);
        return dp[i][sumReq] = take + not_take;
    }
    
    int countPartitions(vector<int>& arr, int diff) {
        // Formula:
        /*
        Pre-requisite:
            a - b = diff
            a + b = total
            2a = total + diff
            a = (total + diff)/2
        */
        
        // Hence, we need to find number of ways we can get a subset of sum (total + diff)/2 
        // total combinations -> 2^n
        // hence, we need to go with dp
        int total = accumulate(arr.begin(), arr.end(), 0);
        if((total + diff) % 2)
            return 0;
        int n = arr.size();
        int sumReq = (total + diff)/2;
        vector<vector<int>> dp(n+1, vector<int>(sumReq+1, -1));
        return get_no_of_ways_to_for_sum(0, sumReq, n, arr, dp);
    }
};


// using DP: Bottom-up Approach: TC: O(n*sum(arr)) SC: O(n*sum(arr))
class Solution {
  public:
    int countPartitions(vector<int>& arr, int diff) {
        // Formula:
        /*
        Pre-requisite:
            a - b = diff
            a + b = total
            2a = total + diff
            a = (total + diff)/2
        */
        
        // Hence, we need to find number of ways we can get a subset of sum (total + diff)/2 
        // total combinations -> 2^n
        // hence, we need to go with dp
        int total = accumulate(arr.begin(), arr.end(), 0);
        if((total + diff) % 2)
            return 0;
        int n = arr.size();
        int sumReq = (total + diff)/2;
        vector<vector<int>> dp(n+1, vector<int>(sumReq+1));
        dp[0][0] = 1;
        for(int s = 1; s <= sumReq; ++s)
            dp[0][s] = 0;
        for(int i = 0; i < n; ++i) {
            int idx = i + 1;
            for(int s = 0; s <= sumReq; ++s) {
                int take = arr[i] <= s ? dp[idx-1][s - arr[i]] : 0;
                int not_take = dp[idx-1][s];
                dp[idx][s] = take + not_take;
            }
        }
        return dp[n][sumReq];
    }
};
