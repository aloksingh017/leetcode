#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> highestPeak(vector<vector<int>> &isWater) {
  int m = isWater.size();
  int n = isWater[0].size();

  queue<pair<int, int>> q;
  vector<vector<int>> height(m, vector<int>(n, INT_MAX));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (1 == isWater[i][j]) {
        q.push({i, j});
        height[i][j] = 0;
      }
    }
  }
  int row[] = {-1, 0, 1, 0};
  int col[] = {0, 1, 0, -1};

  while (!q.empty()) {
    int r = q.front().first;
    int c = q.front().second;
    q.pop();
    for (int i = 0; i < 4; i++) {
      int rc = r + row[i];
      int cc = c + col[i];
      if (0 <= rc && m > rc && 0 <= cc && n > cc && 0 == isWater[rc][cc] &&
          height[rc][cc] == INT_MAX) {
        q.push({rc, cc});
        height[rc][cc] = height[r][c] + 1;
      }
    }
  }
  return height;
}