#include <climits>
#include <iostream>
using namespace std;

// Node structure
class Node {
public:
  int data;
  Node *left;
  Node *right;

  Node(int val) {
    data = val;
    left = nullptr;
    right = nullptr;
  }
};

// Custom data type to keep track of Minimum,Maximum value,
// and Size of the largest BST
class BSTInfo {
public:
  int mini;
  int maxi;
  int mxSz;

  BSTInfo(int mn, int mx, int sz) {
    mini = mn;
    maxi = mx;
    mxSz = sz;
  }
};

// Recursive Function to find maximum size
BSTInfo largestBSTBT(Node *root) {
  if (!root)
    return BSTInfo(INT_MAX, INT_MIN, 0);

  BSTInfo left = largestBSTBT(root->left);
  BSTInfo right = largestBSTBT(root->right);

  // Check if the current subtree is a BST
  if (left.maxi < root->data && right.mini > root->data) {
    return BSTInfo(min(left.mini, root->data), max(right.maxi, root->data),
                   1 + left.mxSz + right.mxSz);
  }

  return BSTInfo(INT_MIN, INT_MAX, max(left.mxSz, right.mxSz));
}

// Function to return the size of the largest BST
int largestBST(Node *root) { return largestBSTBT(root).mxSz; }

int main() {

  // Constructed binary tree
  //         5
  //       /   \
  //      2     4
  //     / \
  //    1   3

  Node *root = new Node(5);
  root->left = new Node(2);
  root->right = new Node(4);
  root->left->left = new Node(1);
  root->left->right = new Node(3);

  cout << largestBST(root) << endl;

  return 0;
}
