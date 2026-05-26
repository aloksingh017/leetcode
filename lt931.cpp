#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, vector<vector<int>> &matrix, vector<vector<int>> &dp) {
  if (j < 0 || j >= matrix.size())
    return INT_MAX;
  if (i == matrix.size() - 1)
    return matrix[i][j];
  if (dp[i][j] != -1)
    return dp[i][j];

  int down = solve(i + 1, j, matrix, dp);
  int left = solve(i + 1, j - 1, matrix, dp);
  int right = solve(i + 1, j + 1, matrix, dp);

  return dp[i][j] = matrix[i][j] + min(down, min(left, right));
}
int minFallingPathSum(vector<vector<int>> &matrix) {
  int n = matrix.size();

  vector<vector<int>> dp = matrix; // copy matrix into dp

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < n; j++) {

      int up = dp[i - 1][j];
      int left = (j > 0) ? dp[i - 1][j - 1] : INT_MAX;
      int right = (j < n - 1) ? dp[i - 1][j + 1] : INT_MAX;

      dp[i][j] += min({up, left, right});
    }
  }

  int ans = INT_MAX;

  for (int j = 0; j < n; j++) {
    ans = min(ans, dp[n - 1][j]);
  }

  return ans;
}