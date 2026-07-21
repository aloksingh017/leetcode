/*
662. Maximum Width of Binary Tree

Given the root of a binary tree, return the maximum width of the given tree.
The maximum width of a tree is the maximum width among all levels.
The width of one level is defined as the length between the end-nodes 
(the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
It is guaranteed that the answer will in the range of a 32-bit signed integer.

Constraints:

The number of nodes in the tree is in the range [1, 3000].
-100 <= Node.val <= 100
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int widthOfBinaryTree(TreeNode *root) {
    int maxwidth = 0;
    queue<pair<TreeNode *, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
      int size = q.size();
      int first = 0, last = 0;
      int index = q.front().second;

      for (int i = 0; i < size; i++) {
        TreeNode *node = q.front().first;
        long long int curid = q.front().second - index;
        q.pop();
        
        if (i == 0)
          first = curid;
        if (i == size - 1)
          last = curid;
        if (node->left)
          q.push({node->left, 2 * curid + 1});
        if (node->right)
          q.push({node->right, 2 * curid + 2});
      }
      maxwidth = max(maxwidth, last - first + 1);
    }
    return maxwidth;
  }
};