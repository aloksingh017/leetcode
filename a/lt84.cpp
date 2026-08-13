/*
leetcode 84: Largest Rectangle in Histogram

Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the above area.

Input: heights = [2,4]
Output: 4
 
Constraints:
1 <= heights.length <= 105
0 <= heights[i] <= 104
*/


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n=heights.size();
        stack<int>s;
        int ans=0;
        int l[n],r[n];
        for(int i=0;i<n;i++){
            while(!s.empty() && heights[s.top()]>=heights[i]) s.pop();
            if(s.empty()) l[i]=0;
            else l[i]=s.top()+1;
            s.push(i);
        }
        while(!s.empty()) s.pop();
        for(int i=n-1;i>=0;i--){
            while(!s.empty() && heights[s.top()]>=heights[i]) s.pop();
            if(s.empty())r[i]=n-1;
            else r[i]=s.top()-1;
            s.push(i);
        }
        for(int i=0;i<n;i++){
            ans=max(ans, (r[i]-l[i]+1)*heights[i]);
        }
        return ans;
    }
};