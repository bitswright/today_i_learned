# Maximum Sum Combination

You are given two integer arrays a[] and b[] of equal size. A sum combination is formed by adding one element from a[] and one from b[], using each index pair (i, j) at most once. Return the top k maximum sum combinations, sorted in non-increasing order.

## Solution
- Using Max-Heap:
    - Code:
        ```cpp
        vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
            // sort both arrays in non-increasing order
            sort(a.begin(), a.end(), greater<int>());
            sort(b.begin(), b.end(), greater<int>());
            
            // create a max-heap {int, {int, int}} to store sum, pair of indices
            // to keep track of maximum sum found so far
            priority_queue<pair<int, pair<int, int>>> maxHeap;
            
            // create a set to keep track of pair of indices that we have included
            // in our answer
            int n = a.size();
            set<pair<int,int>> visited;
            
            // create a vector of int of size k to store final answer
            vector<int> ans(k);
            
            // store first pair in max-heap
            maxHeap.push({a[0] + b[0], {0, 0}});
            visited.insert({0, 0});
            
            for(int p = 0; p < k; ++p) {
                pair<int, pair<int, int>> topPair = maxHeap.top();
                maxHeap.pop();
                
                int pairSum = topPair.first;
                int ai = topPair.second.first;
                int bi = topPair.second.second;
                
                ans[p] = pairSum;
                
                if(ai + 1 < n && visited.find({ai+1, bi}) == visited.end()) {
                    maxHeap.push({a[ai+1] + b[bi], {ai+1, bi}});
                    visited.insert({ai+1, bi});
                }
                if(bi + 1 < n && visited.find({ai, bi+1}) == visited.end()) {
                    maxHeap.push({a[ai] + b[bi+1], {ai, bi+1}});
                    visited.insert({ai, bi+1});
                }
            }
            
            return ans;
        }
        ```
    - TC: O(nlogn)
    - SC: O(k)