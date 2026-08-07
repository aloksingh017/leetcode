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