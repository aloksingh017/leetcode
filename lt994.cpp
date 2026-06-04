int orangesRotting(vector<vector<int>> &grid) {
  int m = grid.size();
  int n = grid[0].size();

  int fresh = 0;
  queue<pair<pair<int, int>, int>> q;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 2) {
        q.push({{i, j}, 0});
        grid[i][j] = -1;
      }
      if (grid[i][j] == 1)
        fresh++;
    }
  }

  int ans = 0;
  int row[] = {-1, 0, 1, 0};
  int col[] = {0, 1, 0, -1};

  int cnt = 0;
  while (!q.empty()) {
    int r = q.front().first.first;
    int c = q.front().first.second;
    int t = q.front().second;
    q.pop();
    ans = max(ans, t);
    for (int i = 0; i < 4; i++) {
      int rc = row[i] + r;
      int cc = col[i] + c;
      if (rc >= 0 && rc < m && cc >= 0 && cc < n && grid[rc][cc] == 1 &&
          grid[rc][cc] != -1) {
        q.push({{rc, cc}, t + 1});
        cnt++;
        grid[rc][cc] = -1;
      }
    }
  }
  return fresh == cnt ? ans : -1;
}