#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int minJumps(vector<int> &arr) {
    unordered_map<int, vector<int>> mp;
    int n = arr.size();
    for (int i = 0; i < n; i++) {
      mp[arr[i]].push_back(i);
    }
    queue<pair<int, int>> q; // index, steps
    q.push({0, 0});
    vector<bool> visit(n, false);

    while (!q.empty()) {
      auto [idx, steps] = q.front();
      q.pop();

      if (n - 1 == idx)
        return steps;
      if (idx - 1 >= 0 && !visit[idx - 1]) {
        visit[idx - 1] = true;
        q.push({idx - 1, steps + 1});
      }

      if (idx + 1 < n && !visit[idx + 1]) {
        visit[idx + 1] = true;
        q.push({idx + 1, steps + 1});
      }
      for (auto it : mp[arr[idx]]) {
        if (!visit[it]) {
          visit[it] = true;
          q.push({it, steps + 1});
        }
      }
      mp[arr[idx]].clear();
    }
    return -1;
  }
};