/*
85. Maximal Rectangle

Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
Example 2:

Input: matrix = [["0"]]
Output: 0
Example 3:

Input: matrix = [["1"]]
Output: 1
 

Constraints:

rows == matrix.length
cols == matrix[i].length
1 <= rows, cols <= 200
matrix[i][j] is '0' or '1'.
*/


class Solution {
public:
     int largestRectangleArea(vector<int>& heights) {
        int ans=0;
        stack<int>s;
        int n=heights.size();
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

    int maximalRectangle(vector<vector<char>>& matrix) {
        int n=matrix.size();
        int m=matrix[0].size();
        int maxarea=0;
        vector<int>height(m,0);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]=='1')
                    height[j]++;
                else height[j]=0;
            }
            int area=largestRectangleArea(height);
            maxarea=max(maxarea,area);
        }
        return maxarea;
    }
};
