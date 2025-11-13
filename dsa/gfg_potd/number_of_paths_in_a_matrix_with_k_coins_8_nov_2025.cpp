// Number of paths in a matrix with k coins

/*
You are given a matrix mat[][] of size n x m, where each of its cells contains some coins. Count the number of ways to collect exactly k coins while moving from the top left cell of the matrix to the bottom right cell.
From a cell (i, j), you can only move to cell (i+1, j) or (i, j+1).

Note: It is guaranteed that the answer will not exceed 32-bit integer limits.

Examples :
Input: k = 12, mat[] = [[1, 2, 3],
                      [4, 6, 5],
                      [3, 2, 1]]
Output: 2
Explanation: There are 2 possible paths with exactly 12 coins, (1 + 2 + 6 + 2 + 1) and (1 + 2 + 3 + 5 + 1).

Input: k = 16, mat[] = [[1, 2, 3], 
                      [4, 6, 5], 
                      [9, 8, 7]]
Output: 0 
Explanation: There are no possible paths that lead to sum = 16.

Constraints:
1 ≤ k ≤ 100
1 ≤ n, m ≤ 100
0 ≤ mat[i][j] ≤ 200

Expected Complexities
Time Complexity: O(n * m * k)
Auxiliary Space: O(n * m * k)
*/

/*
Solution:
On reading this question, we find this question to be a variation of the classic 
BFS/DFS problem of finding all paths from the top-left cell to the bottom-right cell of a matrix 
with an additional constraint of collecting exactly k coins.
But the BFS/DFS approach would take O(2^(n*m)) time.

But while exploring the paths, we can see that there are overlapping subproblems.
Hence, this problem can be solved using Dynamic Programming.
All we need to solve a subproblem is to find number of ways to reach the current cell (i, j) with x coins.
If we can solve this, we can easily build up the solution for the entire matrix.

    Initialize a 3D array dp[n][m][k+1] with first row and column.
    To solve for rest of the cells of the dp, we just need two previous states:
        dp[i][j][x] = dp[i-1][j][x - mat[i][j]] and dp[i][j-1][x - mat[i][j]]
        where x = mat[i][j] to k
    Finally, return dp[n-1][m-1][k].
*/

// Brute Force Approach: O(2^(m*n))
class Solution {
  public:
    int numberOfPath(vector<vector<int>>& mat, int k) {
        int n = mat.size(), m = mat[0].size();
        queue<pair<pair<int, int>, int>> q;
        int ways = 0;
        q.push({{0, 0}, mat[0][0]});
        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            int i = front.first.first;
            int j = front.first.second;
            int c = front.second;
            if(i == n-1 && j == m-1) {
                if(c == k)
                    ways++;
            }
            else if(c <= k) {
                // check right cell
                if(j + 1 < m) 
                    q.push({{i, j+1}, c+mat[i][j+1]});
                // check bottom cell
                if(i + 1 < n) 
                    q.push({{i+1, j}, c+mat[i+1][j]});
            }
        }
        return ways;
    }
};

// Optimal Approach using Dynamic Programming
class Solution {
  public:
    int numberOfPath(vector<vector<int>>& mat, int k) {
        if(mat[0][0] > k) return 0;
        int n = mat.size(), m = mat[0].size();
        
        // Declaring the DP and initializing
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k+1, 0)));
        int sum = 0;
        for(int j = 0; j < m; ++j) {
            sum += mat[0][j];
            if(sum > k)
                break;
            dp[0][j][sum] = 1;
        }
        sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += mat[i][0];
            if(sum > k)
                break;
            dp[i][0][sum] = 1;
        }
        
        // Evaluate DP
        for(int i = 1; i < n; ++i) {
            for(int j = 1; j < m; ++j) {
                if(mat[i][j] > k)
                    break;
                for(int l = mat[i][j]; l <= k; ++l) {
                    dp[i][j][l] = dp[i-1][j][l-mat[i][j]] + dp[i][j-1][l-mat[i][j]];
                }
            }
        }
        
        return dp[n-1][m-1][k];
    }
};