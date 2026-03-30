/*
1707. Maximum XOR With an Element From Array

You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].

The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.

Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.

 
Example 1:
    Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
    Output: [3,3,7]
    Explanation:
    1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
    2) 1 XOR 2 = 3.
    3) 5 XOR 2 = 7.

Example 2:
    Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
    Output: [15,-1,5]
 

Constraints:
    1 <= nums.length, queries.length <= 10^5
    queries[i].length == 2
    0 <= nums[j], xi, mi <= 10^9
*/

struct Node {
    Node* links[2] = {nullptr};

    bool hasBit(int bit) {
        return links[bit] != nullptr;
    }

    void put(int bit) {
        links[bit] = new Node;
    }

    Node* get(int bit) {
        return links[bit];
    }
};

class Trie {
  private:
    Node* root;
  public:
    Trie() {
        root = new Node;
    }

    bool isTrieEmpty() {
        return !root->hasBit(0) && !root->hasBit(1);
    }

    void insert(int n) {
        Node* node = root;
        for(int i = 31; i >= 0; --i) {
            int bit = (n >> i) & 1;
            if(!node->hasBit(bit)) {
                node->put(bit);
            }
            node = node->get(bit);
        }
    }

    int getMaxXor(int n) {
        if(isTrieEmpty())
            return -1;
        Node* node = root;
        int maxXor = 0;
        for(int i = 31; i >= 0; --i) {
            int bit = (n >> i) & 1;
            if(node->hasBit(1 - bit)) {
                node = node->get(1 - bit);
                maxXor = maxXor << 1 | 1;
            } else {
                node = node->get(bit);
                maxXor = maxXor << 1;
            }
        }

        return maxXor;
    }
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        sort(nums.begin(), nums.end());

        int Q = queries.size();
        vector<pair<int, pair<int, int>>> queriesWithIndex(Q);
        for(int i = 0; i < Q; ++i) {
            queriesWithIndex[i] = {queries[i][1], {queries[i][0], i}};
        }
        sort(queriesWithIndex.begin(), queriesWithIndex.end());

        vector<int> responses(Q);
        int ni = 0;
        int N = nums.size();
        Trie trie = Trie();
        for(int i = 0; i < Q; ++i) {
            int mi = queriesWithIndex[i].first;
            int xi = queriesWithIndex[i].second.first;
            int idx = queriesWithIndex[i].second.second;
            while(ni < N && nums[ni] <= mi) {
                trie.insert(nums[ni]);
                ni++;
            }
            responses[idx] = trie.getMaxXor(xi);
        }

        return responses;
    }
};