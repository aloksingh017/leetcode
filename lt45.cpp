#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int jump(vector<int> &nums) {
    int left = 0, right = 0, jumps = 0;
    while (right < nums.size() - 1) {
      int farthest = 0;
      for (int i = left; i <= right; i++) {
        farthest = max(farthest, nums[i] + i);
      }
      left = right + 1;
      right = farthest;
      jumps++;
    }
    return jumps;
  }
};