#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int shortestPathLength(vector<vector<int>> &graph) {
    int n = graph.size();

    // all nodes visited mask
    int finalMask = (1 << n) - 1;
    queue<pair<int, int>> q; //{node, mask}

    // visited[node][mask]
    vector<vector<bool>> visited(n, vector<bool>(1 << n, false));

    // Multi-source BFS
    for (int i = 0; i < n; i++) {
      int mask = (1 << i);
      q.push({i, mask});
      visited[i][mask] = true;
    }

    int steps = 0;

    while (!q.empty()) {
      int sz = q.size();
      while (sz--) {
        auto [node, mask] = q.front();
        q.pop();

        // all visited
        if (mask == finalMask)
          return steps;

        for (auto nei : graph[node]) {
          int newMask = mask | (1 << nei);
          if (!visited[nei][newMask]) {
            visited[nei][newMask] = true;
            q.push({nei, newMask});
          }
        }
      }

      steps++;
    }

    return -1;
  }
};