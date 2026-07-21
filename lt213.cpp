/*
213. House Robber II
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. 
All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. 
Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken 
into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.
Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.
Example 3:

Input: nums = [1,2,3]
Output: 3
 

Constraints:

1 <= nums.length <= 100
0 <= nums[i] <= 1000

*/

#include <bits/stdc++.h>
using namespace std;

// Memomization Approach

int solve(int ind, vector<int> &arr, vector<int> &dp) {
  if (ind < 0)
    return 0;
  if (ind == 0)
    return arr[0];

  if (dp[ind] != -1)
    return dp[ind];

  int notpick = 0 + solve(ind - 1, arr, dp);
  int pick = arr[ind] + solve(ind - 2, arr, dp);

  return dp[ind] = max(pick, notpick);
}
int rob(vector<int> &nums) {
  int n = nums.size();
  if (n == 1)
    return nums[0];
  vector<int> nums1, nums2;

  for (int i = 0; i < n; i++) {
    if (i != 0)
      nums1.push_back(nums[i]);
    if (i != n - 1)
      nums2.push_back(nums[i]);
  }

  vector<int> dp1(n - 1, -1);
  vector<int> dp2(n - 1, -1);

  int sol1 = solve(n - 2, nums1, dp1);
  int sol2 = solve(n - 2, nums2, dp2);

  return max(sol1, sol2);
}

// TABULATION APPROACH

int solve(vector<int> &arr) {
  int n = arr.size();
  vector<int> dp(n, 0);

  dp[0] = arr[0];
  for (int i = 1; i < n; i++) {
    int notpick = dp[i - 1];
    int pick = arr[i];
    if (i > 1)
      pick += dp[i - 2];

    dp[i] = max(pick, notpick);
  }
  return dp[n - 1];
}

int rob(vector<int> &nums) {
  int n = nums.size();
  if (n == 1)
    return nums[0];
  vector<int> nums1, nums2;

  for (int i = 0; i < n; i++) {
    if (i != 0)
      nums1.push_back(nums[i]);
    if (i != n - 1)
      nums2.push_back(nums[i]);
  }

  int sol1 = solve(nums1);
  int sol2 = solve(nums2);

  return max(sol1, sol2);
}