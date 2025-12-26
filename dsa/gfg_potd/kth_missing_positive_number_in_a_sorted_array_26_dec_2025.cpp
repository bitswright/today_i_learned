// Kth Missing Positive Number in a Sorted Array

/*
Given a sorted array of distinct positive integers arr[], You need to find the kth positive number that is missing from the arr[].

Examples :
Input: arr[] = [2, 3, 4, 7, 11], k = 5
Output: 9
Explanation: Missing are 1, 5, 6, 8, 9, 10… and 5th missing number is 9.

Input: arr[] = [1, 2, 3], k = 2
Output: 5
Explanation: Missing are 4, 5, 6… and 2nd missing number is 5.

Input: arr[] = [3, 5, 9, 10, 11, 12], k = 2
Output: 2
Explanation: Missing are 1, 2, 4, 6… and 2nd missing number is 2.

Constraints:
1 ≤ arr.size() ≤ 105
1 ≤ k ≤ 105
1 ≤ arr[i] ≤ 106

Expected Complexities
Time Complexity: O(log n)
Auxiliary Space: O(1)
*/

// Solutions:

// Brute Force Approach: O(n)
/*
Traverse the array from left to right, and for each element find the number of elements missing before this element using:
no_of_elements_missing_before = arr[i] - (i + 1); (+1 because of 0-based indexing)
If no_of_elements_missing_before < k, then move to the next element.
Else return i + k (number of elements present in the array before this element, which is i and we need to add k to compensate the missing elements)
If all elements are traversed and no_of_elements_missing_before < k, then return n + k.

Note: We also derive n+k in one more way:
If we are at index i, then current element is arr[i] and number of elements missing before this element is no_of_elements_missing_before = arr[i] - (i + 1).
And no_of_elements_missing_before >= k, then 
We need arr[i] - (no_of_elements_missing_before - k + 1)
    = arr[i] - no_of_elements_missing_before + k - 1
    = arr[i] - (arr[i] - (i + 1)) + k - 1 
    = arr[i] - arr[i] + (i + 1) + k - 1 
    = i + k
*/
int kthMissing(vector<int> &arr, int k) {
    int n = arr.size();
    for(int i = 0; i < n; ++i) {
        if(arr[i] - i - 1 >= k)
            return i + k;
    }
    return n + k;
}


// Binary Search Approach: O(log n)
/*
Since missing elements before each element are sorted in increasing order, 
we can use binary search to find the very first element before which >= k missing elements, 
and then just return i + k.
*/
int kthMissing(vector<int> &arr, int k) {
    int n = arr.size();
    int s = 0, e = n-1, m;
    while(s <= e) {
        m = (s + e) >> 1;
        if(arr[m] - m - 1 < k)
            s = m + 1;
        else
            e = m - 1;
    }
    return s + k;
}