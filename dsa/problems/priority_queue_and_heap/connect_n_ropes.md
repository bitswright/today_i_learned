# Minimum Cost to connect n ropes

Given an array, arr[] of rope lengths, connect all ropes into a single rope with the minimum total cost. The cost to connect two ropes is the sum of their lengths. 

## Solution

- Using Max-Heap
    - Code:
        ```cpp
        int minCost(vector<int>& arr) {
            int cost = 0;
            priority_queue<int, vector<int>, greater<int>> pq;
            for(int e: arr) {
                pq.push(e);
            }
            while(pq.size() > 1) {
                int rope1 = pq.top();
                pq.pop();
                int rope2 = pq.top();
                pq.pop();
                cost += rope1 + rope2;
                pq.push(rope1 + rope2);
            }
            return cost;
        }
        ```
    - TC: $O(nlogn)$
    - TC: $O(n)$