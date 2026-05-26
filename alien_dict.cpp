#include <bits/stdc++.h>
using namespace std;

// User function Template for C++

class Solution {
public:
  string findOrder(string dict[], int N, int K) {
    // code here
    vector<int> adj[K];
    for (int i = 0; i < N - 1; i++) {
      string s1 = dict[i];
      string s2 = dict[i + 1];
      int minlen = min(s1.size(), s2.size());
      for (int i = 0; i < minlen; i++) {
        if (s1[i] != s2[i]) {
          adj[s1[i] - 'a'].push_back(s2[i] - 'a');
          break;
        }
      }
      vector<int> indeg(K, 0);
      for (int i = 0; i < K; i++) {
        for (auto it : adj[i]) {
          indeg[it]++;
        }
      }
      queue<int> q;
      for (int i = 0; i < K; i++) {
        if (indeg[i] == 0)
          q.push(i);
      }
      vector<int> ans;
      while (!q.empty()) {
        int node = q.front();
        q.pop();
        ans.push_back(node);
        for (auto it : adj[node]) {
          indeg[it]--;
          if (indeg[it] == 0)
            q.push(it);
        }
      }
      string res = "";
      for (auto it : ans) {
        res += char(it + 'a');
      }
      return res;
    }
  };