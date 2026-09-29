/*
994. Rotting Oranges

You are given an m x n grid where each cell can have one of three values:
0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] is 0, 1, or 2.
*/


class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m= grid.size();
        int n= grid[0].size();
        queue<vector<int>>q;

        int fresh=0;

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    q.push({i,j,0});
                    grid[i][j]=-1;
                }
                else if(grid[i][j]==1){
                    fresh++;
                }
                else
                    continue;
            }
        }
        int row[]={-1,0,1,0};
        int col[]={0,1,0,-1};

        int time= 0;
        int cnt=0;
        while(!q.empty()){
            int r= q.front()[0];
            int c= q.front()[1];
            int t= q.front()[2];
            q.pop();
            time= max(time,t);
            for(int i=0;i<4;i++){
                int rc= r+row[i];
                int cc= c+col[i];

                if(rc>=0 && rc<m && cc>=0 && cc<n && grid[rc][cc]==1){
                    cnt++;
                    q.push({rc,cc,t+1});
                    grid[rc][cc]=-1;
                }
            }
        }

        return fresh==cnt?time:-1;
    }
};