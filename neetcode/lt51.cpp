/*
51. N-Queens
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

Example 1:
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.

Example 2:
Input: n = 1
Output: [["Q"]]
 

Constraints:
1 <= n <= 9


Time Complexity: O(N!)
Space Complexity: O(N) (excluding the output)
*/


class Solution {
public:
    vector<vector<string>> ans;

    void solve(int row, int n, vector<string>& board, vector<int>& col, vector<int>& diag1, vector<int>& diag2) {
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int c = 0; c < n; c++) {
            if (col[c] || diag1[row - c + n - 1] || diag2[row + c])
                continue;

            board[row][c] = 'Q';
            col[c] = 1;
            diag1[row - c + n - 1] = 1;
            diag2[row + c] = 1;

            solve(row + 1, n, board, col, diag1, diag2);

            board[row][c] = '.';
            col[c] = 0;
            diag1[row - c + n - 1] = 0;
            diag2[row + c] = 0;
        }
    }

    vector<vector<string>> solveNQueens(int n) {

        vector<string> board(n, string(n, '.'));

        vector<int> col(n, 0);
        vector<int> diag1(2 * n - 1, 0);
        vector<int> diag2(2 * n - 1, 0);

        solve(0, n, board, col, diag1, diag2);

        return ans;
    }
};