/*
3720. Lexicographically Smallest Permutation Greater Than Target

You are given two strings s and target, both having length n, consisting of lowercase English letters.

Return the lexicographically smallest permutation of s that is strictly greater than target. If no permutation of s is lexicographically strictly greater than target, return an empty string.

A string a is lexicographically strictly greater than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears later in the alphabet than the corresponding letter in b.

 

Example 1:
Input: s = "abc", target = "bba"
Output: "bca"
Explanation:
The permutations of s (in lexicographical order) are "abc", "acb", "bac", "bca", "cab", and "cba".
The lexicographically smallest permutation that is strictly greater than target is "bca".

Example 2:
Input: s = "leet", target = "code"
Output: "eelt"
Explanation:
The permutations of s (in lexicographical order) are "eelt", "eetl", "elet", "elte", "etel", "etle", "leet", "lete", "ltee", "teel", "tele", and "tlee".
The lexicographically smallest permutation that is strictly greater than target is "eelt".

Example 3:
Input: s = "baba", target = "bbaa"
Output: ""
Explanation:
The permutations of s (in lexicographical order) are "aabb", "abab", "abba", "baab", "baba", and "bbaa".
None of them is lexicographically strictly greater than target. Therefore, the answer is "".
 

Constraints:

1 <= s.length == target.length <= 300
s and target consist of only lowercase English letters.
 
*/


// Brute force approach 
// Time Complexity: O(n * n!)
// Space Complexity: O(n)

string ans="";
    void generate(string& s, int idx,  string target){
        if(idx>=s.size()){
            if(s>target){
                if(ans.empty() || s<ans)
                    ans = s;
            }
            return;
        }
        for(int i = idx;i<s.size();i++){
            swap(s[i], s[idx]);
            generate(s,idx+1,target);
            swap(s[i], s[idx]);
        }
    }
    string lexGreaterPermutation(string s, string target) {
        generate(s,0,target);
        return ans;
    }



// Optimal
class Solution {
public:
    string result = "";
    
    bool solve(int idx, string s, string cur, string target, vector<int>& freq, bool greater){
        if(idx== target.size()){
            if(cur>target){
                result = cur;
                return true;
            }
            return false;
        }
        for(char ch = 'a'; ch<='z';ch++){
            if(freq[ch-'a']==0)
                continue;
            if(greater == false && ch<target[idx])
                continue;
            cur.push_back(ch);
            freq[ch-'a']--;

            bool isGreater = greater || ch>target[idx];

            if(solve(idx+1, s, cur, target, freq, isGreater))
                return true;

            cur.pop_back();
            freq[ch-'a']++;
        }
        return false;
    }
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> freq(26,0);
        for(int i=0;i<n;i++)
            freq[s[i]-'a']++;
        string cur = "";
        solve(0, s, cur, target, freq, false);
        return result;
    }
};