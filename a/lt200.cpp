/*
200. Number of Islands
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1


Example 2:
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
 
Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] is '0' or '1'.
 
*/


// DFS

class Solution {
public:
    void dfs(vector<vector<char>>& grid,int n, int m,int i,int j){
        if(i<0 || i>=n || j<0 || j>=m || grid[i][j]=='0')
            return;
            grid[i][j]='0';
            dfs(grid,n,m,i-1,j);
            dfs(grid,n,m,i,j+1);
            dfs(grid,n,m,i+1,j);
            dfs(grid,n,m,i,j-1);
        
    }
    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
       int cnt=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='1'){
                    cnt++;
                    dfs(grid,n,m,i,j);
                }
            }
        }
        return cnt;
    }
};


// BFS

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {

        int rows = grid.size();
        int cols = grid[0].size();

        int islands = 0;

        vector<pair<int,int>> dir = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };

        for(int i=0;i<rows;i++) {

            for(int j=0;j<cols;j++) {

                if(grid[i][j]=='0')
                    continue;

                islands++;

                queue<pair<int,int>> q;
                q.push({i,j});
                grid[i][j]='0';

                while(!q.empty()) {

                    auto [r,c]=q.front();
                    q.pop();

                    for(auto d:dir){

                        int nr=r+d.first;
                        int nc=c+d.second;

                        if(nr<0||nc<0||nr>=rows||nc>=cols)
                            continue;

                        if(grid[nr][nc]=='0')
                            continue;

                        grid[nr][nc]='0';
                        q.push({nr,nc});
                    }
                }
            }
        }

        return islands;
    }
};