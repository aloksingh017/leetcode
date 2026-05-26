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