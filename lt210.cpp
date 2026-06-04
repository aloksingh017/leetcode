#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<int> adj[numCourses];
    for (auto it : prerequisites) {
      adj[it[1]].push_back(it[0]);
    }
    vector<int> indeg(numCourses, 0);

    for (int i = 0; i < numCourses; i++) {
      for (auto it : adj[i]) {
        indeg[it]++;
      }
    }
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
      if (indeg[i] == 0)
        q.push(i);
    }

    vector<int> topo;

    while (!q.empty()) {
      int node = q.front();
      q.pop();
      topo.push_back(node);
      for (auto it : adj[node]) {
        indeg[it]--;
        if (indeg[it] == 0)
          q.push(it);
      }
    }
    if (topo.size() == numCourses)
      return topo;
    return {};
  }
};

// optimzed code

class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<int> adj[numCourses];
    vector<int> indeg(numCourses, 0);
    for (auto it : prerequisites) {
      adj[it[1]].push_back(it[0]);
      indeg[it[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++)
      if (0 == indeg[i])
        q.push(i);
    vector<int> ans;
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      ans.push_back(cur);
      for (auto it : adj[cur]) {
        indeg[it]--;
        if (indeg[it] == 0)
          q.push(it);
      }
    }
    return ans.size() == numCourses ? ans : vector<int>{};
  }
};