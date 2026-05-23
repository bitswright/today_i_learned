/*
Transform to Sum Tree

Given a root of a binary tree with n nodes, where each node may contain positive or negative values, convert it into a tree such that each node’s new value is equal to the sum of all values in its left and right subtrees (based on the original tree). For leaf nodes, update their values to 0.

Constraints:
    1 ≤ n ≤ 10^4

Expected Complexities:
    Time Complexity: O(n)
    Auxiliary Space: O(height)
*/

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
    int sumAndUpdateToSumTree(Node *root) {
        if(!root)
            return 0;
        int leftSubTreeSum = sumAndUpdateToSumTree(root->left);
        int rightSubTreeSum = sumAndUpdateToSumTree(root->right);
        int rootValue = root->data;
        root->data = leftSubTreeSum + rightSubTreeSum;
        return leftSubTreeSum + rightSubTreeSum + rootValue;
    }
    
  public:
    void toSumTree(Node *root) {
        sumAndUpdateToSumTree(root);
    }
};