// Ways To Tile A Floor

/*
Given a floor of dimensions 2 x n and tiles of dimensions 2 x 1, the task is to find the number of ways the floor can be tiled. A tile can either be placed horizontally i.e as a 1 x 2 tile or vertically i.e as 2 x 1 tile. 

Note: Two tiling arrangements are considered different if the placement of at least one tile differs.

Examples :
Input: n = 3
Output: 3
Explanation: We need 3 tiles to tile the board of size 2 x 3.
We can tile in following ways:
1) Place all 3 tiles vertically.
2) Place first tile vertically and remaining 2 tiles horizontally.
3) Place first 2 tiles horizontally and remaining tiles vertically.

Input: n = 4
Output: 5
Explanation: We need 4 tiles to tile the board of size 2 x 4.
We can tile in following ways:
1) All 4 vertical
2) All 4 horizontal
3) First 2 vertical, remaining 2 horizontal.
4) First 2 horizontal, remaining 2 vertical.
5) Corner 2 vertical, middle 2 horizontal.

Constraints:
1 ≤ n ≤ 45

Expected Complexities
Time Complexity: O(n)
Auxiliary Space: O(1)
*/

/*
Solution:
This question is a recurring pattern problem.
To cover a floor to 2 x n, we can break the problem into smaller subproblems.
1. If we place the first tile vertically, then we are left with a floor of size 2 x (n-1). -> 1 * ways(n-1)
2. If we place the first tile horizontally, then we have to place the second tile horizontally too under it 
    and then we are left with a floor of size 2 x (n-2) -> 1 * ways(n-2)
Thus, the total number of ways to tile the floor of size 2 x n, ie. ways(n) = ways(n-1) + ways(n-2)
Which is the Fibonacci series.

And since, the subproblems are overlapping, we can also use Dynamic Programming to solve this problem in O(n) time using O(n) space.
*/

class Solution {
  public:
    int numberOfWays(int n) {
        if(n < 3)
            return n;
        int dp[n + 1];
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i <= n; ++i)
            dp[i] = dp[i-1] + dp[i-2];
        return dp[n];
    }
};