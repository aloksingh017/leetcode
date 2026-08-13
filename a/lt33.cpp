/*
33. Search in Rotated Sorted Array

There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that 
the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].
Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:
Input: nums = [1], target = 0
Output: -1
 
Constraints:
1 <= nums.length <= 5000
-104 <= nums[i] <= 104
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-104 <= target <= 104
*/

#include <bits/stdc++.h>
using namespace std;

int search(vector<int> &nums, int target) {
  int low = 0, high = nums.size() - 1;

  while (low <= high) {
    int mid = (low + high) / 2;
    if (nums[mid] == target)
      return mid;
    if (nums[low] <= nums[mid]) {
      if (nums[low] <= target && target <= nums[mid])
        high = mid - 1;
      else
        low = mid + 1;
    } else {
      if (nums[mid] <= target && target <= nums[high])
        low = mid + 1;
      else
        high = mid - 1;
    }
  }
  return -1;
}

int startStation(vector<int> &gas, vector<int> &cost) {
  //  code here
  int totalSurplus = 0;
  int surplus = 0;
  int start = 0;
  for (int i = 0; i < gas.size(); i++) {
    totalSurplus += gas[i] - cost[i];
    surplus += gas[i] - cost[i];
    if (surplus < 0) {
      surplus = 0;
      start = i + 1;
    }
  }
  return totalSurplus < 0 ? -1 : start;
}