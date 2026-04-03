/*
Give a n * n square matrix mat[][], return all the elements of its anti-diagonals from top to bottom.

Examples :
    Input: 
        n = 2, 
        mat[][] = 
            [[1, 2],
             [3, 4]]
    Output: [1, 2, 3, 4]

    Input: 
        n = 3, 
        mat[][] = 
            [[1, 2, 3],
             [4, 5, 6],
             [7, 8, 9]]
    Output: [1, 2, 4, 3, 5, 7, 6, 8, 9]

Constraints:
    1 ≤ n ≤ 10^3
    0 ≤ mat[i][j] ≤ 10^6

Time Complexity: O(n^2)
Auxiliary Space: O(n^2)
*/

/*
// 00 01 02
// 10 11 12
// 20 21 22

// 00          0
// 01 10       1
// 02 11 20    2
// 12 21       3
// 22          4

- Sum of each row is equal to diagonal number.
- If diagonal number is < n, then we are starting row from 0 else D - (N - 1)
- If diagonal number is < n, then we are ending col at 0 else D - (N - 1) 
    (OR)
  If row number is going upto a max of d or n-1.
*/

class Solution {
  public:
    vector<int> diagView(vector<vector<int>> mat) {
        // code here
        vector<int> diagTraversal;
        int n = mat.size();
        for(int d = 0; d < 2*n-1; ++d) {
            int i = d < n ? 0 : d - n + 1;
            int j = d - i;
            while(i <= min(d, n-1)) {
                diagTraversal.push_back(mat[i][j]);
                i++;
                j--;
            }
        } 
        return diagTraversal;
    }
};