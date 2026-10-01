/*
22. Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.


Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:

Input: n = 1
Output: ["()"]
 

Constraints:

1 <= n <= 8
*/


class Solution {
public:
    vector<string> ans;
    void backtrack(int open, int close, string& cur, int n){
        if(cur.size()== 2*n){
            ans.push_back(cur);
            return;
        }
        if(open<n){
            cur.push_back('(');
            backtrack(open+1, close, cur,n);
            cur.pop_back();
        }
        if(close<open){
            cur.push_back(')');
            backtrack(open, close+1, cur,n);
            cur.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        string cur = "";
        backtrack(0, 0, cur, n);
        return ans;
    }
};