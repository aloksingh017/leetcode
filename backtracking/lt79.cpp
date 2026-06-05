/*
Given an m x n grid of characters board and a string word, return true if word
exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where
adjacent cells are horizontally or vertically neighboring. The same letter cell
may not be used more than once.



Example 1:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"ABCCED" Output: true Example 2:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"SEE" Output: true Example 3:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"ABCB" Output: false


Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.


Time Complexity: O(MN⋅3^L)
Space Complexity: O(L)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int len, m, n;
  int row[4] = {-1, 0, 1, 0};
  int col[4] = {0, 1, 0, -1};

  bool find(vector<vector<char>> &board, int i, int j, string &word, int idx) {
    if (idx == len)
      return true;
    if (idx > len)
      return false;
    if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[idx] ||
        board[i][j] == '$')
      return false;

    char temp = board[i][j];
    board[i][j] = '$';
    for (int dir = 0; dir < 4; dir++) {
      int rc = i + row[dir];
      int cc = j + col[dir];
      if (find(board, rc, cc, word, idx + 1))
        return true;
    }
    board[i][j] = temp;
    return false;
  }
  bool exist(vector<vector<char>> &board, string word) {
    m = board.size();
    n = board[0].size();
    len = word.size();

    if (m * n < len)
      return false;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (board[i][j] == word[0] && find(board, i, j, word, 0)) {
          return true;
        }
      }
    }
    return false;
  }
};