/*
399. Evaluate Division

You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] 
and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.
You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.

 

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0
Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]
Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]
 

Constraints:

1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj consist of lower case English letters and digits.
 
*/

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