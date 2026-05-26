#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int minCost(int maxTime, vector<vector<int>> &edges,
              vector<int> &passingFees) {

    int n = passingFees.size();

    vector<vector<pair<int, int>>> graph(n);

    for (auto &e : edges) {
      int u = e[0];
      int v = e[1];
      int t = e[2];

      graph[u].push_back({v, t});
      graph[v].push_back({u, t});
    }

    // {cost, time, node}
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    pq.push({passingFees[0], 0, 0});

    vector<int> minTime(n, INT_MAX);
    minTime[0] = 0;

    while (!pq.empty()) {

      auto curr = pq.top();
      pq.pop();

      int cost = curr[0];
      int time = curr[1];
      int node = curr[2];

      // reached destination
      if (node == n - 1)
        return cost;

      for (auto &nbr : graph[node]) {

        int nextNode = nbr.first;
        int travel = nbr.second;

        int newTime = time + travel;

        if (newTime > maxTime)
          continue;

        int newCost = cost + passingFees[nextNode];

        if (newTime < minTime[nextNode]) {

          minTime[nextNode] = newTime;

          pq.push({newCost, newTime, nextNode});
        }
      }
    }

    return -1;
  }
};