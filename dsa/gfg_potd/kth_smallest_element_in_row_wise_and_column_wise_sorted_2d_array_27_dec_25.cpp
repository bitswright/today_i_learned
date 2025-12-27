// Kth smallest element in a row-wise and column-wise sorted 2D array

/*
Given a matrix mat[][] of size n*n, where each row and column is sorted in non-decreasing order. Find the kth smallest element in the matrix.

Examples :
Input: mat[][] = [[16, 28, 60, 64], k = 3
                [22, 41, 63, 91],
                [27, 50, 87, 93],
                [36, 78, 87, 94]]
Output: 27
Explanation: 27 is the 3rd smallest element.

Input: mat[][] = [[10, 20, 30, 40], k = 7
                [15, 25, 35, 45],
                [24, 29, 37, 48],
                [32, 33, 39, 50]] 
Output: 30
Explanation: 30 is the 7th smallest element.

Constraints:
1 ≤ n ≤ 500
1 ≤ mat[i][j] ≤ 10^4
1 ≤ k ≤ n*n

Expected Complexities
Time Complexity: O(n × log(max(mat) - min(mat)))
Auxiliary Space: O(1)
*/

// Solutions

// Brute Force Approach: O(n^2*log(n^2)) = O(n^2*log(n))
/*
Store all elements in a vector of size n*n and then sort the vector.
Return the k-1 th element from the sorted vector.
*/

// Using Priority Queue: O(n^2*log(k))
/*
1. Create a min-heap (priority queue) to store the elements of the matrix.
2. Keep inserting elements into the min-heap until it contains k elements.
3. If the size of the min-heap exceeds k, remove the largest element.
4. The root of the min-heap will be the kth smallest element.
*/

// Optimal Approach (Binary Search on Answer): O(n*log(max-min))
/*
1. Find the minimum and maximum elements in the matrix. (i.e. mat[0][0] and mat[n-1][n-1])
2. Use binary search on the range [min, max] to find the kth smallest element.
3. In each iteration, count the number of elements smaller than or equal to mid.
4. If count is less than k, search in the right half; otherwise, search in the left half.

Use Binary search on each row/column to find the count of elements smaller than or equal to mid.
*/
int get_number_of_elements_smaller_than_x(vector<vector<int>> &mat, int n, int x) {
    int count = 0;
    for(int r = 0; r < n; ++r) {
        auto lb = lower_bound(mat[r].begin(), mat[r].end(), x);
        count += lb - mat[r].begin();
    }
    return count;
}

int kthSmallest(vector<vector<int>> &mat, int k) {
    int n = mat.size();
    int b = mat[0][0], e = mat[n-1][n-1], m;
    while (b <= e) {
        m = (b + e) >> 1;
        int smallerNumberCount = get_number_of_elements_smaller_than_x(mat, n, m);
        if(smallerNumberCount < k)
            b = m + 1;
        else
            e = m - 1;
    }
    return e;
}