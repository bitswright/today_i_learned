/*
421. Maximum XOR of Two Numbers in an Array

Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.


Example 1:
    Input: nums = [3,10,5,25,2,8]
    Output: 28
    Explanation: The maximum result is 5 XOR 25 = 28.

Example 2:
    Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
    Output: 127


Constraints:
    1 <= nums.length <= 2 * 10^5
    0 <= nums[i] <= 2^31 - 1
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
    int findMaximumXOR(vector<int>& nums) {
        Trie trie = Trie();
        for(int n: nums) {
            trie.insert(n);
        }
        int maxXor = 0;
        for(int n: nums) {
            int nMaxXor = trie.getMaxXor(n);
            maxXor = max(maxXor, nMaxXor);
        }
        return maxXor;
    }
};