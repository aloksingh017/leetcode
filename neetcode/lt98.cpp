/*
98. Validate Binary Search Tree

Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys strictly less than the node's key.
The right subtree of a node contains only nodes with keys strictly greater than the node's key.
Both the left and right subtrees must also be binary search trees.
*/


class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return bst(root,LLONG_MIN,LLONG_MAX);
    }
    bool bst(TreeNode* root, long long minVal, long long maxVal){
        if(root==NULL) return true;
        if(!(minVal<root->val && root->val<maxVal)){
            return false;
        }
        return bst(root->left,minVal,root->val)&& bst(root->right,root->val,maxVal);
    }
};