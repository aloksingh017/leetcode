/*
2096. Step-By-Step Directions From a Binary Tree Node to Another.

You are given the root of a binary tree with n nodes. Each node is uniquely assigned a value from 1 to n. 
You are also given an integer startValue representing the value of the start node s, and a different integer destValue representing the value 
of the destination node t.

Find the shortest path starting from node s and ending at node t. Generate step-by-step directions of such path as a string consisting of only the 
uppercase letters 'L', 'R', and 'U'. Each letter indicates a specific direction:

'L' means to go from a node to its left child node.
'R' means to go from a node to its right child node.
'U' means to go from a node to its parent node.
Return the step-by-step directions of the shortest path from node s to node t.
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    string lcaToStart;
    string lcaToEnd;
    TreeNode* findLCA(TreeNode* root, int startValue, int destValue){
        if(root==NULL || root->val == startValue || root->val== destValue)
            return root;
        TreeNode* left = findLCA(root->left, startValue, destValue);
        TreeNode* right = findLCA(root->right, startValue, destValue);

        if(left==NULL)
            return right;
        else if(right==NULL)
            return left;
        return root;
    }
    void dfs(TreeNode* lcaNode, int startValue, int destValue, string& path){
        if(lcaNode==NULL)
            return;
        if(lcaNode->val == startValue)
            lcaToStart = path;
        if(lcaNode->val == destValue)
            lcaToEnd = path;
        
        path.push_back('L');
        dfs(lcaNode->left, startValue, destValue, path);
        path.pop_back();

        path.push_back('R');
        dfs(lcaNode->right, startValue, destValue, path);
        path.pop_back();
    }
    string getDirections(TreeNode* root, int startValue, int destValue) {
        TreeNode* lcaNode = findLCA(root, startValue, destValue);
        string path="";
        dfs(lcaNode, startValue, destValue, path);

        for(auto& ch: lcaToStart) ch= 'U';
        return lcaToStart+lcaToEnd;
    }
};