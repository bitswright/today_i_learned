/*
Given a fence with n posts and k colours, find out the number of ways of painting the fence so that not more than two consecutive posts have the same colours.
Answers are guaranteed to be fit into a 32 bit integer.

Examples:
    Input: n = 3, k = 2 
    Output: 6
    Explanation: 
        Let the 2 colours be 'R' and 'B'. We have following possible combinations:
        1. RRB
        2. RBR
        3. RBB
        4. BRR
        5. BRB
        6. BBR

    Input: n = 2, k = 4 
    Output: 16
    Explanation: After coloring first post with 4 possible combinations, you can still color next posts with all 4 colors. Total possible combinations will be 4x4=16

Constraints:
    1 ≤ n ≤ 300
    1 ≤ k ≤ 10^5

Time Complexity: O(n)
Auxiliary Space: O(1)
*/

/*
Intution
Count(n) = 
    (k-1)*Count(n-1) {if different color choosen for next} + 
    (k-1)*Count(n-2) {if same color choosen for next}
*/

class Solution {
  public:
    int countWays(int n, int k) {
        if(n == 1)
            return k;
        if(n == 2)
            return k*k;
        int prev2 = k, prev1 = k*k;
        for(int i = 2; i < n; ++i) {
            int temp = prev1*(k-1) + prev2*(k-1);
            prev2 = prev1;
            prev1 = temp;
        }
        return prev1;
    }
};
