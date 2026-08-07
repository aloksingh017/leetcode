/*
863. All Nodes Distance K in Binary Tree

Given the root of a binary tree and an integer target, where the value of the node is unique.
Return an array of all the values in the tree that have a distance of k from the target node.

Example:
Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes at distance 2 from the root with value 5 are 7, 4, and 1.

Constraints:
1. The number of nodes in the tree is in the range [1, 500].
2. Every node's value is unique.
3. 0 <= target <= 500
4. 0 <= k <= 1000
*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void markParent(TreeNode* root,  unordered_map<TreeNode*, TreeNode*>& parentTrack){
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
                TreeNode* cur= q.front();
                q.pop();
                if(cur->left){
                    q.push(cur->left);
                    parentTrack[cur->left]=cur;
                }
                if(cur->right){
                    q.push(cur->right);
                    parentTrack[cur->right]=cur;
                }
        }
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> ans;
        unordered_map<TreeNode*, TreeNode*> parentTrack;
        markParent(root,parentTrack);

        queue<TreeNode*>q;
        q.push(target);
        unordered_map<TreeNode*, bool>vis;
        vis[target]=true;

        int cur_level=0;

        while(!q.empty()){
            int size= q.size();
            if(cur_level++ == k) break;
            for(int i=0;i<size;i++){
                TreeNode* node=q.front();
                q.pop();
                if(node->left && !vis[node->left]){
                    q.push(node->left);
                    vis[node->left]=true;
                }
                if(node->right && !vis[node->right]){
                    q.push(node->right);
                    vis[node->right]=true;
                }
                if(parentTrack[node] && !vis[parentTrack[node]]){
                    q.push(parentTrack[node]);
                    vis[parentTrack[node]]=true;
                }
            }
        }
        while(!q.empty()){
            ans.push_back(q.front()->val);
            q.pop();
        }
        return ans;
    }
};