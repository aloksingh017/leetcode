

class disjointSet {
  vector<int> parent, size;

public:
  disjointSet(int n) {
    parent.resize(n);
    size.resize(n);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
      size[i] = 1;
    }
  }
  int findPar(int node) {
    if (parent[node] == node)
      return node;
    return parent[node] = findPar(parent[node]);
  }

  void unionBySize(int u, int v) {
    int up = findPar(u);
    int vp = findPar(v);
    if (up == vp)
      return;
    if (size[up] < size[vp]) {
      parent[up] = vp;
      size[vp] += size[up];
    } else {
      parent[vp] = up;
      size[up] += size[vp];
    }
  }
};
class Solution {
public:
  // Function to find sum of weights of edges of the Minimum Spanning Tree.
  int spanningTree(int V, vector<vector<int>> adj[]) {
    // code here
    vector<pair<int, pair<int, int>>> edges;

    for (int i = 0; i < V; i++) {
      for (auto it : adj[i]) {
        int adjnode = it[0];
        int wt = it[1];
        int node = i;
        edges.push_back({wt, {node, adjnode}});
      }
    }
    int mstwt = 0;
    disjointSet ds(V);
    sort(edges.begin(), edges.end());

    for (auto it : edges) {
      int u = it.second.first;
      int v = it.second.second;
      int wt = it.first;
      if (ds.findPar(u) != ds.findPar(v)) {
        mstwt += wt;
        ds.unionBySize(u, v);
      }
    }
    return mstwt;
  }
};