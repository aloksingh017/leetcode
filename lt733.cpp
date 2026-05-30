#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                                int color) {
    int m = image.size();
    int n = image[0].size();
    queue<pair<int, int>> q;
    q.push({sr, sc});
    int init = image[sr][sc];
    image[sr][sc] = color;
    int row[] = {-1, 0, 1, 0};
    int col[] = {0, 1, 0, -1};
    while (!q.empty()) {
      int r = q.front().first;
      int c = q.front().second;
      q.pop();
      for (int i = 0; i < 4; i++) {
        int rc = r + row[i];
        int cc = c + col[i];
        if (rc >= 0 && rc < m && cc >= 0 && cc < n && image[rc][cc] == init &&
            image[rc][cc] != color) {
          q.push({rc, cc});
          image[rc][cc] = color;
        }
      }
    }
    return image;
  }
};