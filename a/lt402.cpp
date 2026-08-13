/*
402. Remove K Digits

Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.
Example 1:
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

Example 2:
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

Example 3:
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
 

Constraints:

1 <= k <= num.length <= 105
num consists of only digits.
num does not have any leading zeros except for the zero itself.
*/

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