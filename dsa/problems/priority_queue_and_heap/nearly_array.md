# Nearly Sorted 

Given an array arr[], where each element is at most k positions away from its correct position in the sorted order.
Your task is to restore the sorted order of arr[] by rearranging the elements in place.

Note: Don't use any sort() method.

## Solution

- Using Min-Heap:
    - Code:
        ```cpp
        void nearlySorted(vector<int>& arr, int k) {
            priority_queue<int, vector<int>, greater<int>> minHeap;
            for(int i = 0; i < k; ++i) {
                minHeap.push(arr[i]);
            }
            int n = arr.size();
            for(int i = 0; i < n; ++i) {
                if(i + k < n)
                    minHeap.push(arr[i+k]);
                arr[i] = minHeap.top();
                minHeap.pop();
            }
        }
        ```
    - TC: $O(nlogk)$
    - SC: $O(k)$