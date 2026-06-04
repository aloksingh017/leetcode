/*
Given a string s, rearrange the characters of s so that any two adjacent
characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""


Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
*/

#include <bits/stdc++.h>
using namespace std;

string reorganizeString(string s) {
  vector<int> freq(26, 0);
  for (int i = 0; i < s.size(); i++) {
    freq[s[i] - 'a']++;
  }

  int maxfreq = *max_element(freq.begin(), freq.end());
  int n = s.size();
  if (maxfreq > (n + 1) / 2)
    return "";

  priority_queue<pair<int, char>> pq;

  for (int i = 0; i < 26; i++) {
    if (freq[i] > 0) {
      pq.push({freq[i], char(i + 'a')});
    }
  }

  string ans;
  while (pq.size() >= 2) {
    auto [f1, c1] = pq.top();
    pq.pop();

    ans += c1;

    auto [f2, c2] = pq.top();
    ans += c2;
    pq.pop();

    if (--f1 > 0)
      pq.push({f1, c1});
    if (--f2 > 0)
      pq.push({f2, c2});
  }
  if (!pq.empty()) {
    ans += pq.top().second;
  }
  return ans;
}