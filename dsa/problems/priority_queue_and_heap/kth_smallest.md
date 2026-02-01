# Kth Smallest

Given an integer array arr[] and an integer k, your task is to find and return the kth smallest element in the given array.

Note: The kth smallest element is determined based on the sorted order of the array.

## Solution

- Using Max-Heap
    - Code:
        ```cpp
        int kthSmallest(vector<int> &arr, int k) {
            int n = arr.size();
            priority_queue<int> pq;
            for(int i = 0; i < k; ++i)
                pq.push(arr[i]);
            for(int i = k; i < n; ++i) {
                pq.push(arr[i]);
                pq.pop();
            }
            
            return pq.top();
        }
        ```
    - TC: $O(n)$
    - TC: $O(1)$