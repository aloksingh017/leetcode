/*
540. Single Element in a Sorted Array
You are given a sorted array in which every element appears twice except for one element which 
appears only once.
Find the single element that appears only once.


Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:

Input: nums = [3,3,7,7,10,11,11]
Output: 10
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 100
*/

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
      else`
        high = mid - 1;
    }
  }
  return -1;
}