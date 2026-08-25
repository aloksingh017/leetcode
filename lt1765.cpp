/*
You are given an integer matrix isWater of size m x n that represents a map of land and water cells.

If isWater[i][j] == 0, cell (i, j) is a land cell.
If isWater[i][j] == 1, cell (i, j) is a water cell.
You must assign each cell a height in a way that follows these rules:

The height of each cell must be non-negative.
If the cell is a water cell, its height must be 0.
Any two adjacent cells must have an absolute height difference of at most 1. A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
Find an assignment of heights such that the maximum height in the matrix is maximized.

Return an integer matrix height of size m x n where height[i][j] is cell (i, j)'s height. If there are multiple solutions, return any of them.

 
*/

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