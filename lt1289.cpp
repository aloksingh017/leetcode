#include <bits/stdc++.h>
using namespace std;

int f(int i, int j, vector<vector<int>> &mat, vector<vector<int>> &dp) {
  if (i < 0 || j < 0 || j >= mat[0].size()) {
    return 1e8;
  }

  // if the value is pre-computed then directly return it
  if (dp[i][j] != -1) {
    return dp[i][j];
  }

  if (i == 0) {
    return mat[0][j];
  }

  int mini = 1e8;

  for (int k = 0; k < mat[0].size(); k++) {
    if (k != j) {
      mini = min(mini, mat[i][j] + f(i - 1, k, mat, dp));
    }
  }

  dp[i][j] = mini;

  return dp[i][j];
}

int minFallingPathSum(vector<vector<int>> &grid) {
  int mini = 1e8;
  int n = grid.size(), m = grid[0].size();

  // declared a dp array
  vector<vector<int>> dp(n, vector<int>(m, -1));

  for (int j = 0; j < m; j++) {
    mini = min(mini, f(n - 1, j, grid, dp));
  }

  return mini;
}