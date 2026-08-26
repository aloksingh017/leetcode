/*
417. Pacific Atlantic Water Flow

There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.

Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.






Example 1:


Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[6,7,1,4,5],[5,1,1,2,4],[3,7,1,3,1]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Example 2:

Input: heights = [[1]]
Output: [[0,0]]
 

Constraints:

m == heights.length
n == heights[i].length
1 <= m, n <= 200
0 <= heights[i][j] <= 105
*/


class Solution {
public:
    int m,n;
    void dfs(int row, int col,  vector<vector<bool>>& vis, vector<vector<int>>& heights){
        if(vis[row][col])
            return;
        vis[row][col]=true;
        int dr[4]={-1,0,1,0};
        int dc[4]={0,1,0,-1};

        for(int i=0;i<4;i++){
            int rc  = row+dr[i];
            int cc = col+dc[i];
            if(rc<0 || rc >=m || cc<0 || cc>=n)
                continue;
            if(!vis[rc][cc] && heights[rc][cc]>= heights[row][col]){
                dfs(rc,cc, vis, heights);
            }
        }
    }
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        m = heights.size();
        n = heights[0].size();

        vector<vector<bool>> pacific(m, vector<bool>(n,false));
        vector<vector<bool>> atlan(m, vector<bool>(n,false));

        for(int i=0;i<m;i++){
            dfs(i,0,pacific, heights);
        }
        for(int i=0;i<n;i++){
            dfs(0,i,pacific, heights);
        }
        for(int i=0;i<m;i++){
            dfs(i,n-1,atlan, heights);
        }
        for(int i=0;i<n;i++){
            dfs(m-1, i,atlan, heights);
        }
        vector<vector<int>> ans;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(pacific[i][j] && atlan[i][j])
                    ans.push_back({i,j});
            }
        }
        return ans;
    }
};