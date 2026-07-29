/*
105. Construct Binary Tree from Preorder and Inorder Traversal

Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree,
construct and return the binary tree.


Example 1:
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]


Example 2:
Input: preorder = [-1], inorder = [-1]
Output: [-1]
 

Constraints:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder and inorder consist of unique values.
Each value of inorder also appears in preorder.
preorder is guaranteed to be the preorder traversal of the tree.
inorder is guaranteed to be the inorder traversal of the tree.


Algorithm
Store each value's index from inorder in an unordered_map.
Maintain a pointer preIndex to the current root in preorder.
Recursively:
Create the root using preorder[preIndex].
Find its position in inorder.
Build the left subtree.
Build the right subtree.


Complexity
Time: O(n)
Each node is processed once.
Hash map lookup is O(1).
Space: O(n)
Hash map: O(n)
Recursive call stack: up to O(n) in the worst case (skewed tree), O(log n) for a balanced tree.
*/


class Solution {
public:
    unordered_map<int,int> mp;
    int preIdx = 0;
    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int left, int right){
        if(left>right)
            return NULL;
        int rootval = preorder[preIdx++];
        TreeNode* root = new TreeNode(rootval);

        int mid = mp[rootval];

        root->left = build(preorder, inorder, left, mid-1);
        root->right = build(preorder, inorder, mid+1, right);

        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for(int i=0;i<preorder.size();i++){
            mp[inorder[i]] = i;
        }

        return build(preorder, inorder, 0, n-1);
    }
};