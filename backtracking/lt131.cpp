/*
Given a string s, partition s such that every substring of the partition is a
palindrome. Return all possible palindrome partitioning of s.

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]


Example 2:
Input: s = "a"
Output: [["a"]]


Constraints:

1 <= s.length <= 16
s contains only lowercase English letters.



Time Complexity: O(N⋅2^N)
Space Complexity: O(N)
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int n;
  bool isPallindrome(int right, int left, string &s) {
    while (left < right) {
      if (s[left] != s[right])
        return false;
      left++, right--;
    }
    return true;
  }
  void backtrack(int idx, string &s, vector<string> &cur,
                 vector<vector<string>> &res) {
    if (idx == n) {
      res.push_back(cur);
      return;
    }
    for (int i = idx; i < n; i++) {
      if (isPallindrome(i, idx, s)) {
        cur.push_back(s.substr(idx, i - idx + 1));
        backtrack(i + 1, s, cur, res);
        cur.pop_back();
      }
    }
  }
  vector<vector<string>> partition(string s) {
    n = s.size();
    vector<vector<string>> res;
    vector<string> cur;
    backtrack(0, s, cur, res);
    return res;
  }
};