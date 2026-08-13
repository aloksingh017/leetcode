/*
104. Maximum Depth of Binary Tree
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

 5
   \
    4
   / \   /
 13  8   2
    / \    \
   9   7    1

Input: root = [3,9,20,null,null,15,7]
Output: 3

*/


class Solution {
public:
    int solve(TreeNode* root){
        if(root==NULL)
            return 0;
        int left = solve(root->left);
        int right = solve(root->right);
        return 1+max(left, right);
    }
    int maxDepth(TreeNode* root) {
       return solve(root);
    }
};