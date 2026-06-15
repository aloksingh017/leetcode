/*

39. Combination Sum I

Given an array of distinct integers candidates and a target integer target,
return a list of all unique combinations of candidates where the chosen numbers
sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times.
Two combinations are unique if the frequency of at least one of the chosen
numbers is different.

The test cases are generated such that the number of unique combinations that
sum up to target is less than 150 combinations for the given input.

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple
times. 7 is a candidate, and 7 = 7. These are the only two combinations. Example
2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]
Example 3:

Input: candidates = [2], target = 1
Output: []


Constraints:
1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40


The recursion depth is bounded by target / minCandidate, and each level can
branch into at most N choices. Therefore, the worst-case time complexity is O(N
T/M
), where M is the smallest candidate. The auxiliary space complexity is O(T/M)
due to the recursion stack and current combination path, excluding the output.
*/

class Solution {
public:
  int n;
  void solve(int idx, vector<int> &candidates, int target,
             vector<vector<int>> &res, vector<int> &cur) {
    if (target == 0) {
      res.push_back(cur);
      return;
    }

    for (int i = idx; i < n; i++) {
      if (candidates[i] > target)
        continue;
      cur.push_back(candidates[i]);
      solve(i, candidates, target - candidates[i], res, cur);
      cur.pop_back();
    }
  }
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    n = candidates.size();
    vector<int> cur;
    vector<vector<int>> res;
    solve(0, candidates, target, res, cur);
    return res;
  }
};