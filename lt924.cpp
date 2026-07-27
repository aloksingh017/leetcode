/*
924. Minimize Malware Spread
You are given a network of n nodes represented as an n x n adjacency matrix graph, where the ith node is directly connected to the jth node if graph[i][j] == 1.
Some nodes initial are initially infected by malware. Whenever two nodes are directly connected, and at least one of those two nodes is infected by malware,
both nodes will be infected by malware. This spread of malware will continue until no more nodes can be infected in this manner.

Suppose M(initial) is the final number of nodes infected with malware in the entire network after the spread of malware stops. We will remove exactly one node from initial.
Return the node that, if removed, would minimize M(initial). If multiple nodes could be removed to minimize M(initial), return such a node with the smallest index.

Note that if a node was removed from the initial list of infected nodes, it might still be infected later due to the malware spread.

 

Example 1:

Input: graph = [[1,1,0],[1,1,0],[0,0,1]], initial = [0,1]
Output: 0
Example 2:

Input: graph = [[1,0,0],[0,1,0],[0,0,1]], initial = [0,2]
Output: 0
Example 3:

Input: graph = [[1,1,1],[1,1,1],[1,1,1]], initial = [1,2]
Output: 1
 

Constraints:

n == graph.length
n == graph[i].length
2 <= n <= 300
graph[i][j] is 0 or 1.
graph[i][j] == graph[j][i]
graph[i][i] == 1
1 <= initial.length <= n
0 <= initial[i] <= n - 1
All the integers in initial are unique.

*/

#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
  vector<int> size, parent;

  DisjointSet(int n) {

    size.resize(n, 1);
    parent.resize(n);

    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  int findPar(int node) {

    if (node == parent[node])
      return node;

    return parent[node] = findPar(parent[node]);
  }

  void unionBySize(int u, int v) {

    int ulp_u = findPar(u);
    int ulp_v = findPar(v);

    if (ulp_u == ulp_v)
      return;

    if (size[ulp_u] < size[ulp_v]) {

      parent[ulp_u] = ulp_v;
      size[ulp_v] += size[ulp_u];
    } else {

      parent[ulp_v] = ulp_u;
      size[ulp_u] += size[ulp_v];
    }
  }
};

class Solution {
public:
  int minMalwareSpread(vector<vector<int>> &graph, vector<int> &initial) {

    int n = graph.size();

    DisjointSet ds(n);

    // Build connected components
    for (int i = 0; i < n; i++) {

      for (int j = i + 1; j < n; j++) {

        if (graph[i][j] == 1) {
          ds.unionBySize(i, j);
        }
      }
    }

    // Count infected nodes in each component
    vector<int> infectedCount(n, 0);

    for (auto node : initial) {
      infectedCount[ds.findPar(node)]++;
    }

    sort(initial.begin(), initial.end());

    int maxsave = 0;

    // default answer = smallest node
    int ans = initial[0];

    for (auto node : initial) {

      int root = ds.findPar(node);

      // unique infected node
      if (infectedCount[root] == 1) {

        int saved = ds.size[root];

        if (saved > maxsave) {

          maxsave = saved;
          ans = node;
        }
      }
    }

    return ans;
  }
};