class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        vector<int> arr(s.size(),0);
        for(int i=0;i<s.size();i++){
            if(s[i]=='(')
                st.push(i);
            else{
                if(st.size()>0){
                    int matched_pos= st.top();
                    st.pop();
                    arr[matched_pos]=1;
                    arr[i]=1;
                }
            }
        }
        int ans=0;
        int cnt=0;
        for(int i=0;i<s.size();i++){
            if(arr[i]==1)
                cnt++;
            else cnt=0;
            ans= max(cnt, ans);
        }
        return ans;
    }
};