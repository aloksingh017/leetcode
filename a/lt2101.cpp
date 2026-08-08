/*
2101. Detonate the Maximum Bombs
You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This area is in the shape of a circle with the center as the location of the bomb.
The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb,
 whereas ri denotes the radius of its range.

You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range. 
These bombs will further detonate the bombs that lie in their ranges.

Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.

Example 1:
Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
Output: 5
Explanation: Detonating the bomb at [1,2,3] explodes all 5 bombs.

Example 2:
Input: bombs = [[2,1,3],[6,1,4]]
Output: 2
Explanation: Detonating either bomb explodes both.

Example 3:
Input: bombs = [[1,1,5],[10,10,5]]
Output: 1
Explanation: Detonating either bomb does not explode the other.
 

Constraints:

1 <= bombs.length <= 100
bombs[i].length == 3
1 <= xi, yi, ri <= 105
*/


class Solution {
public:

    int dfs(int node, vector<vector<int>>& graph, vector<int>& visited) {
        visited[node] = 1;
        int count = 1;
        for (int next : graph[node]) {
            if (!visited[next]) {
                count += dfs(next, graph, visited);
            }
        }
        return count;
    }

    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        // Step 1: Build directed graph
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            long long x1 = bombs[i][0];
            long long y1 = bombs[i][1];
            long long r1 = bombs[i][2];
            for (int j = 0; j < n; j++) {
                if (i == j)
                    continue;
                long long x2 = bombs[j][0];
                long long y2 = bombs[j][1];

                long long dx = x1 - x2;
                long long dy = y1 - y2;

                long long distanceSquared = dx * dx + dy * dy;
                if (distanceSquared <= r1 * r1) {
                    graph[i].push_back(j);
                }
            }
        }

        // Step 2: Try starting from every bomb
        int ans = 0;
        for (int i = 0; i < n; i++) {
            vector<int> visited(n, 0);
            int count = dfs(i, graph, visited);
            ans = max(ans, count);
        }
        return ans;
    }
};