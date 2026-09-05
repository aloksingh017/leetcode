/*
847. Shortest Path Visiting All Nodes

You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.

Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

Example 1:
Input: graph = [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]

Example 2:
Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]
 

Constraints:

n == graph.length
1 <= n <= 12
0 <= graph[i].length < n
graph[i] does not contain i.
If graph[a] contains b, then graph[b] contains a.
The input graph is always connected.
 
Time Complexity

The BFS state is represented by:

(node, mask)
node can take n values.
mask can take 2ⁿ values.

Hence, the total number of possible states is n×2^n

Each state is processed at most once because of the visited array. For every processed state, you iterate through all neighbors of node.

Across all states, each edge can be explored for every possible mask.

Therefore, O((n+m)⋅2^n)

Space
O(n.2^n))
*/


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int shortestPathLength(vector<vector<int>> &graph) {
    int n = graph.size();

    // all nodes visited mask
    int finalMask = (1 << n) - 1;
    queue<pair<int, int>> q; //{node, mask}

    // visited[node][mask]
    vector<vector<bool>> visited(n, vector<bool>(1 << n, false));

    // Multi-source BFS
    for (int i = 0; i < n; i++) {
      int mask = (1 << i);
      q.push({i, mask});
      visited[i][mask] = true;
    }

    int steps = 0;

    while (!q.empty()) {
      int sz = q.size();
      while (sz--) {
        auto [node, mask] = q.front();
        q.pop();

        // all visited
        if (mask == finalMask)
          return steps;

        for (auto nei : graph[node]) {
          int newMask = mask | (1 << nei);
          if (!visited[nei][newMask]) {
            visited[nei][newMask] = true;
            q.push({nei, newMask});
          }
        }
      }

      steps++;
    }
    return -1;
  }
};