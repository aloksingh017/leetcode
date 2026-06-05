/*
You are given an m x n integer array grid where grid[i][j] could be:

1 representing the starting square. There is exactly one starting square.
2 representing the ending square. There is exactly one ending square.
0 representing empty squares we can walk over.
-1 representing obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending
square, that walk over every non-obstacle square exactly once.



Example 1:


Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
Example 2:


Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
Example 3:


Input: grid = [[0,1],[2,0]]
Output: 0
Explanation: There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.


Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 20
1 <= m * n <= 20
-1 <= grid[i][j] <= 2
There is exactly one starting cell and one ending cell.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int emptycells;
  int m, n;
  int row[4] = {-1, 0, 1, 0};
  int col[4] = {0, 1, 0, -1};
  int cnt;
  void dfs(vector<vector<int>> &grid, int start_x, int start_y, int cur_cnt) {
    if (0 > start_x || m <= start_x || 0 > start_y || n <= start_y ||
        grid[start_x][start_y] == -1)
      return;
    if (grid[start_x][start_y] == 2) {
      if (cur_cnt == emptycells)
        cnt++;
      return;
    }
    int og = grid[start_x][start_y];
    grid[start_x][start_y] = -1;
    for (int i = 0; i < 4; i++) {
      int rc = start_x + row[i];
      int cc = start_y + col[i];
      dfs(grid, rc, cc, cur_cnt + 1);
    }
    grid[start_x][start_y] = og;
  }
  int uniquePathsIII(vector<vector<int>> &grid) {
    m = grid.size();
    n = grid[0].size();
    emptycells = 0;
    cnt = 0;
    int start_x = 0;
    int start_y = 0;

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (1 == grid[i][j]) {
          start_x = i;
          start_y = j;
        }
        if (0 == grid[i][j])
          emptycells++;
      }
    }
    emptycells++;
    int cur_cnt = 0;
    dfs(grid, start_x, start_y, cur_cnt);
    return cnt;
  }
};