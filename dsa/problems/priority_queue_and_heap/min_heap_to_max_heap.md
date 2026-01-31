# Convert Min Heap to Max Heap

You are given an array arr of N integers representing a min Heap. The task is to convert it to max Heap.

A max-heap is a complete binary tree in which the value in each internal node is greater than or equal to the values in the children of that node. 

## Solution

- Starting from the first non-leaf node from the bottom `(n/2)-1`, perform heapify function.
- Since, heap is already an array satisfying complete binary tree property, we just need to satisfy heap property.
- Leaf nodes are already heapified, hence we start from the first non-leaf node.
- Note: We call heapify on a node when we are not concerned about it's ancestors, and it's decendents are already heapified but this node might not be satisfying heap property.
- Code:
    ```cpp
    void heapify(vector<int> &arr, int N, int i) {
        int maxValueIndex = i;
        if(2*i+1 < N && arr[maxValueIndex] < arr[2*i+1])
            maxValueIndex = 2*i+1;
        if(2*i+2 < N && arr[maxValueIndex] < arr[2*i+2])
            maxValueIndex = 2*i+2;
        if(maxValueIndex != i) {
            swap(arr[i], arr[maxValueIndex]);
            heapify(arr, N, maxValueIndex);
        }
    }
    void convertMinToMaxHeap(vector<int> &arr, int N) {
        for(int i = N/2-1; i >= 0; --i) {
            heapify(arr, N, i);
        }
    }
    ```
    - TC: $O(n)$
    - SC: $O(1)$