/*
778. Swim in Rising Water
You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).

It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.

You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. 
Of course, you must stay within the boundaries of the grid during your swim.

Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).


Input: grid = [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.


Example 2:
Input: grid = [[0,1,2,3,4],
               [24,23,22,21,5],
               [12,13,14,15,16],
               [11,17,18,19,20],
               [10,9,8,7,6]]
Output: 16


Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 50
0 <= grid[i][j] < n^2
Each value grid[i][j] is unique

*/


// Bruteforce
// Time:  O(n⁴)
// Space: O(n²)

class Solution {
public:
    int n;
    
    bool canReach(int t, vector<vector<int>>& grid) {
        if (grid[0][0] > t)
            return false;
        
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        queue<pair<int, int>> q;
        
        q.push({0, 0});
        visited[0][0] = true;
        
        int directions[5] = {0, 1, 0, -1, 0};
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            if (r == n - 1 && c == n - 1)
                return true;
            
            for (int i = 0; i < 4; i++) {
                int nr = r + directions[i];
                int nc = c + directions[i + 1];
                
                if (nr >= 0 && nr < n &&
                    nc >= 0 && nc < n &&
                    !visited[nr][nc] &&
                    grid[nr][nc] <= t) {
                    
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        
        return false;
    }
    
    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size();
        
        for (int t = 0; t < n * n; t++) {
            if (canReach(t, grid))
                return t;
        }
        
        return -1;
    }
};


// Better approach
Time:  O(n² log n)
Space: O(n²)

class Solution {
public:
    bool check(vector<vector<int>>& grid, int time){
        if(grid[0][0]>time)
            return false;
        int n = grid.size();
        vector<vector<int>> visited(n, vector<int>(n, false));
        queue<pair<int,int>> q;
        q.push({0,0});

        int dr[4]={-1,0,1,0};
        int dc[4]={0,1,0,-1};
        while(!q.empty()){
            auto [r,c] = q.front();
            q.pop();
            if(r==n-1 && c==n-1)
                return true;
            for(int i=0;i<4;i++){
                int rc = r+dr[i];
                int cc = c+dc[i];
                if(rc>=0 && rc<n && cc>=0 && cc<n && !visited[rc][cc] && grid[rc][cc]<=time){
                    visited[rc][cc] = true;
                    q.push({rc,cc});
                }
            }
        }
        return false;
    }
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int low = max(grid[0][0], grid[n-1][n-1]); 
        int high = n*n-1;
        while(low<=high){
            int mid = (low+high)/2;
            if(check(grid,mid)){
                high = mid-1;
            }
            else
                low = mid+1;
        }
        return low;
    }
};

// using priority_queue
// Time:  O(n² log n)
// Space: O(n²)

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> visited(n, vector<int>(n, false));
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({grid[0][0], 0,0});


        int dr[4]={-1,0,1,0};
        int dc[4]={0,1,0,-1};
        int ans = -1;
        while(!pq.empty()){
            auto cur = pq.top();
            int h = cur[0];
            int r = cur[1];
            int c = cur[2];
            pq.pop();

            ans  = max(ans, h);
            if(r==n-1 && c==n-1)
                return ans;

            for(int i=0;i<4;i++){
                int rc = r+dr[i];
                int cc = c+dc[i];
                if(rc>=0 && rc<n && cc>=0 && cc<n && !visited[rc][cc]){
                    visited[rc][cc] = true;
                    pq.push({grid[rc][cc],rc,cc});
                }
            }
        }
        return -1;
    }
};