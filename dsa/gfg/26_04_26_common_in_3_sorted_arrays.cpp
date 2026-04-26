/*
Given three sorted arrays in non-decreasing order, return all common elements in non-decreasing order across these arrays. If there are no such elements return an empty array.
Note: Ignore duplicates, include each common element only once in the output.

Examples:
    Input: a[] = [1, 5, 10, 20, 40, 80], b[] = [6, 7, 20, 80, 100], c[] = [3, 4, 15, 20, 30, 70, 80, 120]
    Output: [20, 80]
    Explanation: The elements 20 and 80 appear in all three arrays a, b, and c, making them the only common elements, so the output is [20, 80].

    Input: a[] = [1, 2, 3, 4, 5], b[] = [6, 7], c[] = [8, 9, 10]
    Output: []
    Explanation: Since none of the elements in arrays a, b, and c appear in all three arrays, there are no common elements, so the output is [].

    Input:  a[] = [1, 1, 1, 2, 2, 2], b[] = [1, 1, 2, 2, 2], c[] = [1, 1, 1, 1, 2, 2, 2, 2]
    Output: [1, 2]
    Explanation: Ignoring duplicates, 1 and 2 are present in all three arrays, so the output is [1, 2].

Constraints:
    1 ≤ a.size(), b.size(), c.size() ≤ 10^5
    -10^5 ≤ a[i], b[i], c[i] ≤ 10^5

Time Complexity: O(n)
Auxiliary Space: O(1)
*/

class Solution {
    void increment(vector<int> &arr, int size, int &i) {
        i++;
        while(i < size && arr[i-1] == arr[i])
            i++;
    }

  public:
    vector<int> commonElements(vector<int> &a, vector<int> &b, vector<int> &c) {
        int aSize = a.size(), bSize = b.size(), cSize = c.size();
        int i = 0, j = 0, k = 0;
        vector<int> res;
        while(i < aSize && j < bSize && k < cSize) {
            if(a[i] == b[j] && b[j] == c[k]) {
                res.push_back(a[i]);
                increment(a, aSize, i);
                increment(b, bSize, j);
                increment(c, cSize, k);
            } else {
                int min = a[i];
                if(b[j] < min)
                    min = b[j];
                if(c[k] < min)
                    min = c[k];
                if(a[i] == min)
                    increment(a, aSize, i);
                if(b[j] == min)
                    increment(b, bSize, j);
                if(c[k] == min)
                    increment(c, cSize, k);
            }
        }
        return res;
    }
};
