/*
You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell has one of three values:

0 represents grass,
1 represents fire,
2 represents a wall that you and fire cannot pass through.
You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the bottom-right cell, 
(m - 1, n - 1). Every minute, you may move to an adjacent grass cell. After your move, every fire cell will spread to all adjacent cells 
that are not walls.

Return the maximum number of minutes that you can stay in your initial position before moving while still safely reaching the safehouse. 
If this is impossible, return -1. If you can always reach the safehouse regardless of the minutes stayed, return 109.

Note that even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely reaching the safehouse.

A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> fireTime;

  int maximumMinutes(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    fireTime.assign(m, vector<int>(n, 1e9));

    queue<pair<int, int>> q;

    // multi-source fire BFS
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {

        if (grid[i][j] == 1) {
          q.push({i, j});
          fireTime[i][j] = 0;
        }
      }
    }

    int row[] = {-1, 0, 1, 0};
    int col[] = {0, 1, 0, -1};

    // fire spread BFS
    while (!q.empty()) {
      auto [r, c] = q.front();
      q.pop();

      for (int k = 0; k < 4; k++) {
        int nr = r + row[k];
        int nc = c + col[k];

        if (nr < 0 || nr >= m || nc < 0 || nc >= n)
          continue;

        if (grid[nr][nc] == 2)
          continue;

        if (fireTime[nr][nc] > fireTime[r][c] + 1) {

          fireTime[nr][nc] = fireTime[r][c] + 1;
          q.push({nr, nc});
        }
      }
    }

    int low = 0;
    int high = 1e9;
    int ans = -1;

    while (low <= high) {
      int mid = low + (high - low) / 2;

      if (canReach(grid, mid)) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return ans >= 1e8 ? 1000000000 : ans;
  }

  bool canReach(vector<vector<int>> &grid, int wait) {

    int m = grid.size();
    int n = grid[0].size();

    queue<vector<int>> q;

    vector<vector<int>> vis(m, vector<int>(n, 0));

    q.push({0, 0, wait});

    vis[0][0] = 1;

    int row[] = {-1, 0, 1, 0};
    int col[] = {0, 1, 0, -1};

    while (!q.empty()) {

      auto curr = q.front();
      q.pop();

      int r = curr[0];
      int c = curr[1];
      int time = curr[2];

      // fire already here
      if (time >= fireTime[r][c] &&
          !(r == m - 1 && c == n - 1 && time == fireTime[r][c]))
        continue;

      // reached safehouse
      if (r == m - 1 && c == n - 1)
        return true;

      for (int i = 0; i < 4; i++) {

        int nr = r + row[i];
        int nc = c + col[i];

        if (nr < 0 || nr >= m || nc < 0 || nc >= n)
          continue;

        if (grid[nr][nc] == 2)
          continue;

        if (vis[nr][nc])
          continue;

        vis[nr][nc] = 1;

        q.push({nr, nc, time + 1});
      }
    }

    return false;
  }
};


// 


class Solution {
public:
    bool canReach(vector<vector<int>>& grid, int wait){
        queue<vector<int>>q;
        q.push({0,0,wait});

        vector<vector<int>> vis(m,vector<int>(n,0));
        vis[0][0]=1;
        while(!q.empty()){
            int r=q.front()[0];
            int c=q.front()[1];
            int time= q.front()[2];
            q.pop();
            if(time>=fireTime[r][c] && !(r==m-1 && c==n-1 && fireTime[r][c]==time))
                continue;
            
            if(r==m-1 && c==n-1)
                return true;
            
            for(int i=0;i<4;i++){
                int rc= r+row[i];
                int cc= c+col[i];

                if(rc<0 || rc>=m || cc<0 ||cc>=n || grid[rc][cc]==2 || vis[rc][cc]==1) 
                    continue;
                vis[rc][cc]=1;
                q.push({rc,cc,time+1});
            }
        }
        return false;
    }
    vector<vector<int>> fireTime;
    int row[4]={-1,0,1,0};
    int col[4]={0,1,0,-1};
    int m,n;

    int maximumMinutes(vector<vector<int>>& grid) {
        m= grid.size();
        n= grid[0].size();
        fireTime.assign(m,vector<int>(n,1e9));

        queue<pair<int,int>>q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    q.push({i,j});
                    fireTime[i][j]=0;
                }
            }
        }

        while(!q.empty()){
            int r= q.front().first;
            int c= q.front().second;
            q.pop();

            for(int i=0;i<4;i++){
                int rc= r+row[i];
                int cc= c+col[i];
                if(rc<0 || rc>=m || cc<0 || cc>=n || grid[rc][cc]==2){
                    continue;
                }

                if(fireTime[rc][cc]>fireTime[r][c]+1){
                    fireTime[rc][cc]=1+fireTime[r][c];
                    q.push({rc,cc});
                }
            }
        }

        int low=0, high=1e9;
        int ans=-1;
        while(low<=high){
            int mid= low+(high-low)/2;
            if(canReach(grid,mid)){
                ans=mid;
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
        return ans>=1e8?1e9:ans;
    }
};