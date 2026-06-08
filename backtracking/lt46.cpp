/*
46. Permutations
Given an array nums of distinct integers, return all the possible permutations.
You can return the answer in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]


Example 2:
Input: nums = [0,1]
Output: [[0,1],[1,0]]
Example 3:

Input: nums = [1]
Output: [[1]]


Constraints:

1 <= nums.length <= 6
-10 <= nums[i] <= 10
All the integers of nums are unique.
ime	O(n · n!)
Auxiliary Space	O(n)
Space including output	O(n · n!)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int n;
  void backtrack(int idx, vector<int> &nums, vector<vector<int>> &res) {
    if (idx == n) {
      res.push_back(nums);
      return;
    }
    for (int i = idx; i < n; i++) {
      swap(nums[idx], nums[i]);
      backtrack(idx + 1, nums, res);
      swap(nums[idx], nums[i]);
    }
  }
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> res;
    n = nums.size();
    backtrack(0, nums, res);
    return res;
  }
};