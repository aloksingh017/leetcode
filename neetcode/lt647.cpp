/*
647. Palindromic Substrings

Given a string s, return the number of palindromic substrings in it.
A string is a palindrome when it reads the same backward as forward.
A substring is a contiguous sequence of characters within the string.

 

Example 1:
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.
*/


// bruteforce  solution
//  Time Complexity: O(n^3)
// Space Complexity: O(1)


class Solution {
public:
    bool isPalindrome(string &s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r])
                return false;
            l++;
            r--;
        }
        return true;
    }

    int countSubstrings(string s) {
        int n = s.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isPalindrome(s, i, j))
                    ans++;
            }
        }

        return ans;
    }
};


// Better (Dynamic Programming)
// Time Complexity: O(n^2)
// Space Complexity: O(n^2)

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();

        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int ans = 0;

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (len == 1)
                    dp[i][j] = true;

                else if (len == 2)
                    dp[i][j] = (s[i] == s[j]);

                else
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
                if (dp[i][j])
                    ans++;
            }
        }
        return ans;
    }
};

