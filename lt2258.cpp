#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> fireTime;

  int maximumMinutes(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    fireTime.assign(m, vector<int>(n, 1e9));

    queue<pair<int, int>> q;

    // multi-source fire BFS
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {

        if (grid[i][j] == 1) {
          q.push({i, j});
          fireTime[i][j] = 0;
        }
      }
    }

    int row[] = {-1, 0, 1, 0};
    int col[] = {0, 1, 0, -1};

    // fire spread BFS
    while (!q.empty()) {
      auto [r, c] = q.front();
      q.pop();

      for (int k = 0; k < 4; k++) {
        int nr = r + row[k];
        int nc = c + col[k];

        if (nr < 0 || nr >= m || nc < 0 || nc >= n)
          continue;

        if (grid[nr][nc] == 2)
          continue;

        if (fireTime[nr][nc] > fireTime[r][c] + 1) {

          fireTime[nr][nc] = fireTime[r][c] + 1;
          q.push({nr, nc});
        }
      }
    }

    int low = 0;
    int high = 1e9;
    int ans = -1;

    while (low <= high) {

      int mid = low + (high - low) / 2;

      if (canReach(grid, mid)) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return ans >= 1e8 ? 1000000000 : ans;
  }

  bool canReach(vector<vector<int>> &grid, int wait) {

    int m = grid.size();
    int n = grid[0].size();

    queue<vector<int>> q;

    vector<vector<int>> vis(m, vector<int>(n, 0));

    q.push({0, 0, wait});

    vis[0][0] = 1;

    int row[] = {-1, 0, 1, 0};
    int col[] = {0, 1, 0, -1};

    while (!q.empty()) {

      auto curr = q.front();
      q.pop();

      int r = curr[0];
      int c = curr[1];
      int time = curr[2];

      // fire already here
      if (time >= fireTime[r][c] &&
          !(r == m - 1 && c == n - 1 && time == fireTime[r][c]))
        continue;

      // reached safehouse
      if (r == m - 1 && c == n - 1)
        return true;

      for (int i = 0; i < 4; i++) {

        int nr = r + row[i];
        int nc = c + col[i];

        if (nr < 0 || nr >= m || nc < 0 || nc >= n)
          continue;

        if (grid[nr][nc] == 2)
          continue;

        if (vis[nr][nc])
          continue;

        vis[nr][nc] = 1;

        q.push({nr, nc, time + 1});
      }
    }

    return false;
  }
};