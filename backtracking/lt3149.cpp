/*
3149. Find the Minimum Cost Array Permutation

You are given an array nums which is a permutation of [0, 1, 2, ..., n - 1].
The score of any permutation of [0, 1, 2, ..., n - 1] named perm is defined as:
score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... +
|perm[n - 1] - nums[perm[0]]|

Return the permutation perm which has the minimum possible score.
If multiple permutations exist with this score, return the one that is
lexicographically smallest among them.


Input: nums = [1,0,2]

Output: [0,1,2]

Explanation:



The lexicographically smallest permutation with minimum cost is [0,1,2]. The
cost of this permutation is |0 - 0| + |1 - 2| + |2 - 1| = 2.

Example 2:

Input: nums = [0,2,1]

Output: [0,2,1]

Explanation:



The lexicographically smallest permutation with minimum cost is [0,2,1]. The
cost of this permutation is |0 - 1| + |2 - 2| + |1 - 0| = 2.



Constraints:

2 <= n == nums.length <= 14
nums is a permutation of [0, 1, 2, ..., n - 1].



//T.C : O(n!)
//S.C : O(n)
*/

class Solution {
public:
  int n;
  int minSum = INT_MAX;
  vector<int> result;

  void solve(vector<int> &nums, vector<bool> &visited, vector<int> &temp,
             int sum) {
    if (minSum <= sum)
      return;

    if (temp.size() == n) {
      sum += abs(temp.back() - nums[temp[0]]);
      if (sum < minSum) {
        minSum = sum;
        result = temp;
      }
    }

    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        visited[i] = true;
        temp.push_back(i);
        solve(nums, visited, temp,
              sum + abs(temp[temp.size() - 2] - nums[temp[temp.size() - 1]]));
        temp.pop_back();
        visited[i] = false;
      }
    }
  }

  vector<int> findPermutation(vector<int> &nums) {
    n = nums.size();
    vector<bool> visited(n, false);
    vector<int> temp = {0};
    visited[0] = true;

    solve(nums, visited, temp, 0);
    return result;
  }
};