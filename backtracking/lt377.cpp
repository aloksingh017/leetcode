/*
377. Combination Sum IV

Given an array of distinct integers nums and a target integer target, return the
number of possible combinations that add up to target.

The test cases are generated so that the answer can fit in a 32-bit integer.

Example 1:
Input: nums = [1,2,3], target = 4
Output: 7
Explanation:
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.
Example 2:

Input: nums = [9], target = 3
Output: 0

Constraints:

1 <= nums.length <= 200
1 <= nums[i] <= 1000
All the elements of nums are unique.
1 <= target <= 1000

Follow up: What if negative numbers are allowed in the given array?
How does it change the problem? What limitation we need to add to the question
to allow negative numbers?
*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> dp = vector<vector<int>>(1001, vector<int>(201, -1));
int n;
int backtrack(int idx, vector<int> &nums, int target) {
  if (target == 0)
    return 1;
  if (idx >= n || target < 0)
    return 0;
  if (dp[target][idx] != -1)
    return dp[target][idx];

  int take_idx = backtrack(0, nums, target - nums[idx]);
  int rejext_idx = backtrack(idx + 1, nums, target);
  return dp[target][idx] = take_idx + rejext_idx;
}
int combinationSum4(vector<int> &nums, int target) {
  n = nums.size();
  return backtrack(0, nums, target);
}