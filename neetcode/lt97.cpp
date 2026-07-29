/*
97. Interleaving String

Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration where s and t are divided into n and m substrings respectively, such that:

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
Note: a + b is the concatenation of strings a and b.

Example 1:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true
Explanation: One way to obtain s3 is:
Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
Since s3 can be obtained by interleaving s1 and s2, we return true.
Example 2:

Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false
Explanation: Notice how it is impossible to interleave s2 with any other string to obtain s3.
Example 3:

Input: s1 = "", s2 = "", s3 = ""
Output: true
 

Constraints:

0 <= s1.length, s2.length <= 100
0 <= s3.length <= 200
s1, s2, and s3 consist of lowercase English letters.

Follow up: Could you solve it using only O(s2.length) additional memory space?
*/

bool solve(int i, int j, vector<vector<int>>& dp,string& s1, string& s2, string& s3){
        if(i==s1.size() && j== s2.size())
            return true;
        if(dp[i][j] != -1)
            return dp[i][j];
        bool ans = false;
        int k = i+j;
        if(i<s1.size() && s1[i]==s3[k]){
            ans |= solve(i+1, j, dp, s1,s2,s3);
        }
        if(j<s2.size() && s2[j]==s3[k]){
            ans |= solve(i,j+1,dp,s1,s2,s3);
        }

        return dp[i][j]= ans;
    }
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size();
        int n = s2.size();
        int k = s3.size();

        if(m+n != k)
            return false;
        vector<vector<int>> dp(m+1, vector<int>(n+1,-1));

        return solve(0,0, dp, s1, s2, s3);
    }