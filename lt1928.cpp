/*
1928. Minimum Cost to Reach Destination in Time

There is a country of n cities numbered from 0 to n - 1 where all the cities are connected by bi-directional roads. The roads are represented as a 2D integer array edges where edges[i] = [xi, yi, timei] denotes a road between cities xi and yi that takes timei minutes to travel. There may be multiple roads of differing travel times connecting the same two cities, but no road connects a city to itself.
Each time you pass through a city, you must pay a passing fee. This is represented as a 0-indexed integer array passingFees of length n where passingFees[j] is the amount of dollars you must pay when you pass through city j.
In the beginning, you are at city 0 and want to reach city n - 1 in maxTime minutes or less. The cost of your journey is the summation of passing fees for each city that you passed through at some moment of your journey (including the source and destination cities).
Given maxTime, edges, and passingFees, return the minimum cost to complete your journey, or -1 if you cannot complete it within maxTime minutes.


*/
class Solution {
public:
  int minCost(int maxTime, vector<vector<int>> &edges, vector<int> &passingFees) {
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