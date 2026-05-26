#include <bits/stdc++.h>
using namespace std;

int singleNonDuplicate(vector<int> &nums) {
  if (nums.size() == 1)
    return nums[0];
  int low = 0, high = nums.size() - 1;
  int n = nums.size();
  while (low <= high) {
    int mid = (low + high) / 2;
    if (mid == 0 && nums[mid] != nums[mid + 1])
      return nums[mid];
    if (mid == n - 1 && nums[n - 1] != nums[n - 2])
      return nums[n - 1];

    if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1])
      return nums[mid];

    if (mid % 2 == 0) {
      if (nums[mid] == nums[mid - 1])
        high = mid - 1;
      else
        low = mid + 1;
    } else {
      if (nums[mid] == nums[mid - 1])
        low = mid + 1;
      else
        high = mid - 1;
    }
  }
  return -1;
}