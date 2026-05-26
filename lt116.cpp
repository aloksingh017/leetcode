#include <bits/stdc++.h>
using namespace std;

Node *connect(Node *root) {
  if (root == NULL)
    return root;
  queue<Node *> q;
  q.push(root);

  while (!q.empty()) {
    int size = q.size();
    Node *rightNode = NULL;
    for (int i = 0; i < size; i++) {
      Node *cur = q.front();
      q.pop();
      cur->next = rightNode;
      rightNode = cur;
      if (cur->right)
        q.push(cur->right);
      if (cur->left)
        q.push(cur->left);
    }
  }
  return root;
}