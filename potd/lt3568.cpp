/*
3568. Minimum Moves to Clean the Classroom

You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:

'S': Starting position of the student
'L': Litter that must be collected (once collected, the cell becomes empty)
'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
'X': Obstacle the student cannot pass through
'.': Empty space
You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.

Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.

Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.

Example 1:
Input: classroom = ["S.", "XL"], energy = 2
Output: 2
Explanation:
The student starts at cell (0, 0) with 2 units of energy.
Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
A valid sequence of moves to collect all litter is as follows:
Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
The student collects all the litter using 2 moves. Thus, the output is 2.

Example 2:
Input: classroom = ["LS", "RL"], energy = 4
Output: 3
Explanation:
The student starts at cell (0, 1) with 4 units of energy.
A valid sequence of moves to collect all litter is as follows:
Move 1: From (0, 1) → (0, 0) to collect the first litter 'L' with 1 unit of energy used and 3 units remaining.
Move 2: From (0, 0) → (1, 0) to 'R' to reset and restore energy back to 4.
Move 3: From (1, 0) → (1, 1) to collect the second litter 'L'.
The student collects all the litter using 3 moves. Thus, the output is 3.

Example 3:
Input: classroom = ["L.S", "RXL"], energy = 3
Output: -1
Explanation:
No valid path collects all 'L'.

Constraints:

1 <= m == classroom.length <= 20
1 <= n == classroom[i].length <= 20
classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
1 <= energy <= 50
There is exactly one 'S' in the grid.
There are at most 10 'L' cells in the grid.
 
*/

Why normal BFS (row, col) is not enough?
Suppose you reach the same cell in two situations:

Situation A                           Situation B
Position = (2,3)                      Position = (2,3)
Energy = 5                          Energy = 2
Collected = {L1}                    Collected = {L1, L2}

Although the position is the same, these are completely different states.

So our BFS state must be:

(row, col, remainingEnergy, collectedLitterMask)

This is the key observation.

// Better approach

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr, sc;
        int litterCount = 0;

        // Store index of every litter cell
        vector<vector<int>> litterIndex(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    litterIndex[i][j] = litterCount++;
                }
            }
        }

        // No litter
        if (litterCount == 0)
            return 0;

        int targetMask = (1 << litterCount) - 1;

        // visited[row][col][energyLeft][mask]
        vector<vector<vector<vector<bool>>>> visited(m, vector<vector<vector<bool>>>(n, vector<vector<bool>>( energy + 1, vector<bool>(1 << litterCount, false))));

        // {row, col, remainingEnergy, mask}
        queue<vector<int>> q;

        q.push({sr, sc, energy, 0});
        visited[sr][sc][energy][0] = true;

        int moves = 0;

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto state = q.front();
                q.pop();

                int r = state[0];
                int c = state[1];
                int currEnergy = state[2];
                int mask = state[3];

                // All litter collected
                if (mask == targetMask)
                    return moves;

                // Cannot move further
                if (currEnergy == 0)
                    continue;

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = currEnergy - 1;
                    int newMask = mask;

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        int idx = litterIndex[nr][nc];
                        newMask |= (1 << idx);
                    }

                    if (!visited[nr][nc][newEnergy][newMask]) {
                        visited[nr][nc][newEnergy][newMask] = true;
                        q.push({nr, nc, newEnergy, newMask});
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};


// optimal approach

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        int litterCount = 0;

        vector<vector<int>> litterIndex(
            m, vector<int>(n, -1)
        );

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    litterIndex[i][j] = litterCount++;
                }
            }
        }

        if (litterCount == 0)
            return 0;

        int targetMask = (1 << litterCount) - 1;

        // bestEnergy[row][col][mask]
        // Maximum energy with which we have reached this state
        vector<vector<vector<int>>> bestEnergy(
            m,
            vector<vector<int>>(
                n,
                vector<int>(1 << litterCount, -1)
            )
        );

        // {row, col, currentEnergy, mask}
        queue<array<int, 4>> q;

        q.push({sr, sc, energy, 0});
        bestEnergy[sr][sc][0] = energy;

        int moves = 0;

        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, 1, 0, -1};

        while (!q.empty()) {

            int size = q.size();

            while (size--) {

                auto [r, c, curEnergy, mask] = q.front();
                q.pop();

                if (mask == targetMask)
                    return moves;

                if (curEnergy == 0)
                    continue;

                for (int i = 0; i < 4; i++) {

                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n ||
                        classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = curEnergy - 1;
                    int newMask = mask;

                    if (classroom[nr][nc] == 'R')
                        newEnergy = energy;

                    if (classroom[nr][nc] == 'L') {
                        int idx = litterIndex[nr][nc];
                        newMask |= (1 << idx);
                    }

                    // Only process if we reach with MORE energy
                    if (newEnergy > bestEnergy[nr][nc][newMask]) {

                        bestEnergy[nr][nc][newMask] = newEnergy;

                        q.push({
                            nr,
                            nc,
                            newEnergy,
                            newMask
                        });
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};