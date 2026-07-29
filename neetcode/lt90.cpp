/*
90. Subsets II

Given an integer array nums that may contain duplicates, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:
Input: nums = [0]
Output: [[],[0]]
 

Constraints:

1 <= nums.length <= 10
-10 <= nums[i] <= 10


Complexity
Time: O(n × 2ⁿ)
There are up to 2ⁿ subsets, and copying each subset into the answer takes up to O(n) time.
Space: O(n) for the recursion stack (excluding the output).

Complexity
Time: O(n × 2ⁿ)
There are up to 2ⁿ subsets, and copying each subset into the answer takes up to O(n) time.
Space: O(n) for the recursion stack (excluding the output).
*/


class Solution {
public:
    vector<vector<int>> ans;
    vector<int> curr;

    void backtrack(vector<int>& nums, int start) {
        ans.push_back(curr);

        for (int i = start; i < nums.size(); i++) {

            if (i > start && nums[i] == nums[i - 1])
                continue;

            curr.push_back(nums[i]);

            backtrack(nums, i + 1);

            curr.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        backtrack(nums, 0);

        return ans;
    }
};