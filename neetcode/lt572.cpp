/*
572. Subtree of Another Tree
Given the roots of two binary trees root and subRoot, return true if there is a subtree of root with the same structure and node values of subRoot and false otherwise.
A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. The tree tree could also be considered as a subtree of itself.

Expample 1:
Input: root = [3,4,5,1,2], subRoot = [4,1,2]
Output: true


Expample 2:
Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
Output: false
 

Constraints:

The number of nodes in the root tree is in the range [1, 2000].
The number of nodes in the subRoot tree is in the range [1, 1000].
-104 <= root.val <= 104
-104 <= subRoot.val <= 104

N = number of nodes in root
M = number of nodes in subRoot
Time: O(N × M) in the worst case (checking isSame at many nodes).
Space: O(H) for recursion, where H is the height of the tree.

*/

bool isSame(TreeNode* root, TreeNode* subRoot){
        if(root == NULL && subRoot == NULL)
            return true;
        if(root == NULL || subRoot == NULL)
            return false;
        return (root->val == subRoot->val) && isSame(root->left, subRoot->left) && isSame(root->right, subRoot->right);
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(root == NULL)
            return false;
        if(isSame(root, subRoot))
            return true;
        
        return isSubtree(root->left, subRoot) ||
       isSubtree(root->right, subRoot);
    }