# Is Array K Sorted

Given an array of n distinct elements. Check whether the given array is a k-sorted array or not. A k-sorted array is an array where each element is at most k distance away from its target position in the sorted array. 
Return "Yes" if the array is a k-sorted array else return "No".

## Solution

- Using Max-Heap:
    - Code
        ```cpp
        string isKSortedArray(int arr[], int n, int k) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            for(int i = 0; i < n; ++i) {
                pq.push({arr[i], i});
            }
            int c = 0;
            while(!pq.empty()) {
                if(abs(pq.top().second - c) > k)
                    return "No";
                pq.pop();
                c++;
            }
            return "Yes";
        }
        ```
    - TC: $O(nlogk)$
    - SC: $O(k)$