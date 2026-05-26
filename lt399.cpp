#include <bits/stdc++.h>
using namespace std;

void dfs(unordered_map<string, vector<pair<string, double>>> &adj,
         unordered_set<string> &vis, string src, string dest, double &ans,
         double product) {
  if (vis.find(src) != vis.end()) {
    return;
  }
  if (src == dest) {
    ans = product;
    return;
  }
  vis.insert(src);
  for (auto it : adj[src]) {
    string v = it.first;
    double val = it.second;
    dfs(adj, vis, v, dest, ans, product * val);
  }
}
vector<double> calcEquation(vector<vector<string>> &equations,
                            vector<double> &values,
                            vector<vector<string>> &queries) {
  int n = equations.size();
  unordered_map<string, vector<pair<string, double>>> adj;
  for (int i = 0; i < n; i++) {
    string u = equations[i][0];
    string v = equations[i][1];
    double value = values[i];
    adj[u].push_back({v, value});
    adj[v].push_back({u, 1.0 / value});
  }

  vector<double> result;
  for (auto query : queries) {
    double ans = -1.0;
    double product = 1.0;
    string src = query[0];
    string dest = query[1];
    if (adj.find(src) != adj.end() && adj.find(dest) != adj.end()) {
      unordered_set<string> vis;
      dfs(adj, vis, src, dest, ans, product);
    }
    result.push_back(ans);
  }
  return result;
}