#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int cameras = 0;

  // States
  // 0 -> NEEDS CAMERA
  // 1 -> HAS CAMERA
  // 2 -> COVERED

  int dfs(TreeNode *root) {

    // Null nodes are already covered
    if (root == NULL)
      return 2;

    int left = dfs(root->left);
    int right = dfs(root->right);

    // If any child needs camera,
    // place camera here
    if (left == 0 || right == 0) {

      cameras++;

      return 1;
    }

    // If any child has camera,
    // current node is covered
    if (left == 1 || right == 1)
      return 2;

    // Children are covered,
    // but current node is not
    return 0;
  }

  int minCameraCover(TreeNode *root) {

    // If root still needs camera
    if (dfs(root) == 0)
      cameras++;

    return cameras;
  }
};