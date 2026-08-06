/*
139. Word Break

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.
Note that the same word in the dictionary may be reused multiple times in the segmentation.

Example 1:
Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".


Example 2:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.


Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
 
*/


// bruetforce approach 
//Time Complexity: O(2^n)
// Space complexity: O(n)

 int n;
    bool solve(int idx, unordered_set<string>& dict, string& s){
        if(idx==n)
            return true;
        for(int end = idx;end<n;end++){
            string subword = s.substr(idx, end-idx+1);
            if(dict.count(subword) && solve(end+1, dict, s))
                return true;
        }
        return false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        n = s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return solve(0, dict, s);
    }


// DP Memoization approach 
//Time Complexity: O(n^3)
// Space complexity: O(n)

solve(0)
    loop n times
       substr O(n)

solve(1)
    loop n-1 times
       substr O(n)

solve(2)
    loop n-2 times
       substr O(n)

...
class Solution {
public:
    int n;
    bool solve(int idx, unordered_set<string>& dict, string& s, vector<int> & dp){
        if(idx==n)
            return true;
        if(dp[idx]!=-1)
            return dp[idx];
        for(int end = idx;end<n;end++){
            string subword = s.substr(idx, end-idx+1);
            if(dict.count(subword) && solve(end+1, dict, s,dp))
                return dp[idx] =true;
        }
        return dp[idx] =false;
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        n = s.size();
        vector<int> dp(n,-1);
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return solve(0, dict, s, dp);
    }
};