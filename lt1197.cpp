#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int minKnightMoves(int x, int y) {
    x = abs(x);
    y = abs(y);
    queue<pair<int, int>> q;
    q.push({0, 0});
    int steps = 0;
    vector<vector<int>> vis(301, vector<int>(301, 0));
    vis[0][0] = 1;
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    while (!q.empty()) {
      int size = q.size();
      while (size--) {
        auto [currx, curry] = q.front();
        q.pop();
        if (currx == x && curry == y)
          return steps;
        for (int i = 0; i < 8; i++) {
          int nx = currx + dx[i];
          int ny = curry + dy[i];
          if (nx >= -1 && ny >= -1 && nx <= x + 1 && ny <= y + 1 &&
              !vis[nx][ny]) {
            vis[nx][ny] = 1;
            q.push({nx, ny});
          }
        }
      }
      steps++;
    }
    return -1;
  }
};