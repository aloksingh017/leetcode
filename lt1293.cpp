#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int shortestPath(vector<vector<int>> &grid, int k) {
    int m = grid.size();
    int n = grid[0].size();

    if (m == 1 && n == 1)
      return 0;

    queue<vector<int>> q;
    q.push({0, 0, k});

    vector<vector<int>> vis(m, vector<int>(n, -1));
    vis[0][0] = k;

    int steps = 0;

    int row[] = {-1, 0, 1, 0};
    int col[] = {0, 1, 0, -1};

    while (!q.empty()) {
      int size = q.size();
      while (size--) {
        auto it = q.front();
        q.pop();
        int r = it[0];
        int c = it[1];
        int rem = it[2];
        if (r == m - 1 && c == n - 1)
          return steps;
        for (int i = 0; i < 4; i++) {
          int rc = r + row[i];
          int cc = c + col[i];

          if (rc < 0 || rc >= m || cc < 0 || cc >= n)
            continue;

          int newK = rem - grid[rc][cc];
          if (newK < 0)
            continue;

          if (vis[rc][cc] >= newK)
            continue;

          vis[rc][cc] = newK;
          q.push({rc, cc, newK});
        }
      }
      steps++;
    }
    return -1;
  }
};