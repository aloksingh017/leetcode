#include <bits/stdc++.h>
using namespace std;

// Memomization Approach

int solve(int ind, vector<int> &nums, vector<int> &dp) {
  if (ind < 0)
    return 0;
  if (ind == 0)
    return nums[0];
  if (dp[ind] != -1)
    return dp[ind];
  int notpick = 0 + solve(ind - 1, nums, dp);
  int pick = INT_MIN;
  pick = nums[ind] + solve(ind - 2, nums, dp);
  return dp[ind] = max(pick, notpick);
}
int rob(vector<int> &nums) {
  int n = nums.size();
  vector<int> dp(n, -1);
  return solve(n - 1, nums, dp);
}

// Tabulation Approach

int rob(vector<int> &nums) {
  int n = nums.size();
  if (n == 1)
    return nums[0];

  int prev2 = nums[0];
  int prev1 = max(nums[0], nums[1]);

  for (int ind = 2; ind < n; ind++) {
    int notpick = prev1;
    int pick = nums[ind] + prev2;
    int cur = max(pick, notpick);
    prev2 = prev1;
    prev1 = cur;
  }
  return prev1;
}