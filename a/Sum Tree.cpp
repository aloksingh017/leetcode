/*
Given the root of a Binary Tree with n nodes, check whether it is a Sum Tree and return true if it is, otherwise return false.

A Sum Tree is a Binary Tree in which the value of every non-leaf node is equal to the sum of all nodes present in its left and right subtrees. 
An empty tree and a leaf node are also considered Sum Trees.

*/

class Solution {
  public:
    int check(Node* root){
        if(root== NULL)
            return 0;
            
        if(root->left ==NULL && root->right == NULL)
            return root->data;
            
        int leftSum = check(root->left);
        if(leftSum==-1)
            return -1;
            
        int rightSum = check(root->right);
        if(rightSum==-1)
            return -1;
            
        if(root->data != leftSum+rightSum)
            return -1;
            
        return root->data+leftSum+rightSum;
    }
    bool isSumTree(Node* node) {
        // code here
        return check(node) != -1;
    }
};