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