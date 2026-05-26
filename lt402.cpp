#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  string removeKdigits(string num, int k) {
    stack<char> st;
    for (auto digit : num) {
      while (k > 0 && !st.empty() && digit < st.top()) {
        st.pop();
        k--;
      }
      st.push(digit);
    }
    while (k > 0 && !st.empty()) {
      st.pop();
      k--;
    }
    string temp = "";
    while (!st.empty()) {
      temp += st.top();
      st.pop();
    }
    reverse(temp.begin(), temp.end());
    int m = temp.size();
    string res = "";
    int flag = 0;
    for (int i = 0; i < m; i++) {
      if (temp[i] == '0' && flag == 0) {
        continue;
      } else {
        res += temp[i];
        flag = 1;
      }
    }
    if (res.size() == 0)
      res += '0';
    return res;
  }
};