/*
1345. Jump Game IV
Given an array of integers arr, you are initially positioned at the first index of the array.

In one step you can jump from index i to index:

i + 1 where: i + 1 < arr.length.
i - 1 where: i - 1 >= 0.
j where: arr[i] == arr[j] and i != j.
Return the minimum number of steps to reach the last index of the array.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
Example 2:

Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You do not need to jump.
Example 3:

Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index of the array.
 

Constraints:

1 <= arr.length <= 5 * 104
-108 <= arr[i] <= 108
 
*/

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