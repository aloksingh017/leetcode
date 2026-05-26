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