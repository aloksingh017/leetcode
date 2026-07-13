/*
49. Group Anagrams
Given an array of strings strs, group the anagrams together. You can return the answer in any order.
Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Explanation:
There is no string in strs that can be rearranged to form "bat".
The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.

Example 2:
Input: strs = [""]
Output: [[""]]

Example 3:
Input: strs = ["a"]
Output: [["a"]]

Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.
*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> mp;
    for (auto str : strs) {
      vector<int> freq(26, 0);
      for (int i = 0; i < str.size(); i++) {
        freq[str[i] - 'a']++;
      }
      string key = "";
      for (int i = 0; i < 26; i++) {
        key += to_string(freq[i]) + '#';
      }
      mp[key].push_back(str);
    }
    vector<vector<string>> ans;

    for (auto it : mp) {
      ans.push_back(it.second);
    }
    return ans;
  }
};