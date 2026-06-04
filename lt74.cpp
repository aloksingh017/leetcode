/*
You are given an m x n integer matrix matrix with the following two properties:

Each row is sorted in non-decreasing order.
The first integer of each row is greater than the last integer of the previous
row. Given an integer target, return true if target is in matrix or false
otherwise.

You must write a solution in O(log(m * n)) time complexity.

Example 1:

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true
Example 2:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false


Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-104 <= matrix[i][j], target <= 104

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  bool solve(vector<int> nums, int target) {
    int low = 0, high = nums.size() - 1;
    while (low <= high) {
      int mid = (low + high) / 2;
      if (nums[mid] == target)
        return true;
      else if (nums[mid] > target)
        high = mid - 1;
      else
        low = mid + 1;
    }
    return false;
  }
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int row = matrix.size();
    int col = matrix[0].size();
    for (int i = 0; i < row; i++) {
      if (matrix[i][0] <= target && target <= matrix[i][col - 1]) {
        if (solve(matrix[i], target))
          return true;
      }
    }
    return false;
  }
};

// TC: O(m log n)
// SC: O(1)

//   optimized code

bool searchMatrix(vector<vector<int>> &matrix, int target) {
  int row = matrix.size();
  int col = matrix[0].size();

  int low = 0, high = row * col - 1;

  while (low <= high) {
    int mid = (low + high) / 2;
    int value = matrix[mid / col][mid % col];
    if (value == target)
      return true;
    else if (value < target)
      low = mid + 1;
    else
      high = mid - 1;
  }
  return false;
}