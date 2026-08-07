
/*
2385. Amount of Time for Binary Tree to Be Infected

You are given the root of a binary tree with unique values, and an integer start. At minute 0, an infection starts from the node with value start.
Each minute, a node becomes infected if:
The node is currently uninfected.
The node is adjacent to an infected node.
Return the number of minutes needed for the entire tree to be infected.

 

Example 1:
Input: root = [1,5,3,null,4,10,6,9,2], start = 3
Output: 4
Explanation: The following nodes are infected during:
- Minute 0: Node 3
- Minute 1: Nodes 1, 10 and 6
- Minute 2: Node 5
- Minute 3: Node 4
- Minute 4: Nodes 9 and 2
It takes 4 minutes for the whole tree to be infected so we return 4.
Example 2:
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  TreeNode *helper(TreeNode *root,
                   unordered_map<TreeNode *, TreeNode *> &parentTrack,
                   int start) {
    queue<TreeNode *> q;
    q.push(root);
    TreeNode *startNode;

    while (!q.empty()) {
      TreeNode *node = q.front();
      if (node->val == start)
        startNode = node;
      q.pop();
      if (node->left) {
        q.push(node->left);
        parentTrack[node->left] = node;
      }
      if (node->right) {
        q.push(node->right);
        parentTrack[node->right] = node;
      }
    }
    return startNode;
  }
  int calculateTime(unordered_map<TreeNode *, TreeNode *> &parentTrack,
                    TreeNode *startNode) {
    unordered_map<TreeNode *, int> vis;
    vis[startNode] = 1;
    queue<TreeNode *> q;
    q.push(startNode);
    int time = 0;

    while (!q.empty()) {
      int size = q.size();
      int flag = 0;
      for (int i = 0; i < size; i++) {
        TreeNode *node = q.front();
        q.pop();
        if (node->left && !vis[node->left]) {
          q.push(node->left);
          flag = 1;
          vis[node->left] = 1;
        }
        if (node->right && !vis[node->right]) {
          q.push(node->right);
          vis[node->right] = 1;
          flag = 1;
        }
        if (parentTrack[node] && !vis[parentTrack[node]]) {
          q.push(parentTrack[node]);
          vis[parentTrack[node]] = 1;
          flag = 1;
        }
      }
      if (flag)
        time++;
    }
    return time;
  }
  int amountOfTime(TreeNode *root, int start) {
    unordered_map<TreeNode *, TreeNode *> parentTrack;
    TreeNode *startNode = helper(root, parentTrack, start);
    int time = calculateTime(parentTrack, startNode);
    return time;
  }
};