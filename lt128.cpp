#include <bits/stdc++.h>
using namespace std;

int longestConsecutive(vector<int> &nums) {
  if (nums.size() == 0)
    return 0;

  int len = 1;
  unordered_set<int> st;

  for (int i = 0; i < nums.size(); i++) {
    st.insert(nums[i]);
  }

  for (auto it : st) {
    if (st.find(it - 1) == st.end()) {
      int cnt = 1;
      int x = it;
      while (st.find(x + 1) != st.end()) {
        cnt++;
        x++;
      }
      len = max(len, cnt);
    }
  }
  return len;
}