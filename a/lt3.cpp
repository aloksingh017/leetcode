/*
3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without duplicate characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 105
s consists of English letters, digits, symbols and spaces.
 
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size()==0)
            return 0;
        vector<int> hash(256,-1);
        int ans = 0;
        int left = 0, right=0;
        while(right<s.size()){
            if(hash[s[right]]!=-1){
                left = max(left, hash[s[right]]+1);
            }
            hash[s[right]]=right;
            ans = max(ans, right-left+1);
            right++;
        }
        return ans;
    }
};