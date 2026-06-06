/*
Given an integer array nums, return all the different possible non-decreasing
subsequences of the given array with at least two elements. You may return the
answer in any order.

Example 1:
Input: nums = [4,6,7,7]
Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

Example 2:
Input: nums = [4,4,3,2,1]
Output: [[4,4]]


Constraints:

1 <= nums.length <= 15
-100 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int n;
  void backtrack(int idx, vector<int> &cur, vector<vector<int>> &res,
                 vector<int> &nums) {
    if (2 <= cur.size()) {
      res.push_back(cur);
    }

    unordered_set<int> st;

    for (int i = idx; i < n; i++) {
      if ((cur.empty() || nums[i] >= cur.back()) &&
          st.find(nums[i]) == st.end()) {
        cur.push_back(nums[i]);
        backtrack(i + 1, cur, res, nums);
        cur.pop_back();
        st.insert(nums[i]);
      }
    }
  }
  vector<vector<int>> findSubsequences(vector<int> &nums) {
    n = nums.size();
    vector<vector<int>> res;
    vector<int> cur;
    backtrack(0, cur, res, nums);
    return res;
  }
};