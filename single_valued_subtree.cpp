// User function Template for C++

/* Tree Node
struct Node
{
    int data;
    Node* left;
    Node* right;
};*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  bool singlevaluedRec(Node *root, int &cnt) {
    if (root == NULL)
      return true;

    bool left = singlevaluedRec(root->left, cnt);
    bool right = singlevaluedRec(root->right, cnt);

    if (left == false || right == false)
      return false;
    if (root->left && root->data != root->left->data)
      return false;
    if (root->right && root->data != root->right->data)
      return false;

    cnt++;
    return true;
  }
  int singlevalued(Node *root) {
    // code here
    int cnt = 0;
    singlevaluedRec(root, cnt);
    return cnt;
  }
};