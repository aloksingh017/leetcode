
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
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