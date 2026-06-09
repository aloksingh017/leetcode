/*
17. Letter Combinations of a Phone Number

Given a string containing digits from 2-9 inclusive, return all possible letter
combinations that the number could represent. Return the answer in any order. A
mapping of digits to letters (just like on the telephone buttons) is given
below. Note that 1 does not map to any letters.

Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
Example 2:

Input: digits = "2"
Output: ["a","b","c"]


Constraints:
1 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].


Time: O(4^n)
Space: O(n)
*/

class Solution {
public:
  vector<string> res;
  int n;
  void backtrack(int idx, string &temp, string &digits,
                 unordered_map<char, string> &mp) {
    if (idx >= n) {
      res.push_back(temp);
      return;
    }
    char ch = digits[idx];
    string str = mp[ch];

    for (int i = 0; i < str.size(); i++) {
      temp.push_back(str[i]);
      backtrack(idx + 1, temp, digits, mp);
      temp.pop_back();
    }
  }
  vector<string> letterCombinations(string digits) {
    n = digits.size();
    if (n == 0)
      return res;

    unordered_map<char, string> mp;
    mp['2'] = "abc";
    mp['3'] = "def";
    mp['4'] = "ghi";
    mp['5'] = "jkl";
    mp['6'] = "mno";
    mp['7'] = "pqrs";
    mp['8'] = "tuv";
    mp['9'] = "wxyz";

    string temp = "";
    backtrack(0, temp, digits, mp);
    return res;
  }
};