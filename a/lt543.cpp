/*
543. Diameter of Binary Tree

Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.


*/

class Solution {
public:
    int solve(TreeNode* root, int& dia){
        if(root==NULL)
            return 0;
        int left = solve(root->left, dia);
        int right = solve(root->right, dia);
        dia = max(dia, left+right);
        return 1+ max(left,right);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int dia=0;
        solve(root, dia);
        return dia;
    }
};