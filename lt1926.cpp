#include <bits/stdc++.h>

using namespace std;
int nearestExit(vector<vector<char>> &maze, vector<int> &entrance) {
  int m = maze.size();
  int n = maze[0].size();

  queue<pair<int, int>> q;
  q.push({entrance[0], entrance[1]});

  maze[entrance[0]][entrance[1]] = '+'; // visited

  int row[] = {-1, 0, 1, 0};
  int col[] = {0, 1, 0, -1};
  int steps = 0;
  while (!q.empty()) {
    int size = q.size();
    while (size--) {
      auto [r, c] = q.front();
      q.pop();
      if ((r == 0 || r == m - 1 || c == 0 || c == n - 1) &&
          !(r == entrance[0] && c == entrance[1]))
        return steps;

      for (int i = 0; i < 4; i++) {
        int rc = r + row[i];
        int cc = c + col[i];

        if (rc >= 0 && rc < m && cc >= 0 && cc < n && '.' == maze[rc][cc]) {
          maze[rc][cc] = '+';
          q.push({rc, cc});
        }
      }
    }

    steps++;
  }
  return -1;
}