class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        if(n==0)
            return 0;
        vector<int> hash(256,-1);
        int maxlen = 0;
        int left = 0, right = 0;
        while(right<n){
            if(hash[s[right]]!=-1){
                left = max(left, hash[s[right]]+1);
            }
            hash[s[right]] = right;
            maxlen = max(maxlen, right-left+1);
            right++;
        }
        return maxlen;
    }
};