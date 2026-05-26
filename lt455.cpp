Assume you are an awesome parent and want to give your children some
    cookies.But,
    you should give each child at most one cookie.

    Each child i has a greed factor g[i],
    which is the minimum size of a cookie that the child will be content with;
and each cookie j has a size s[j].If s[j] >= g[i],
    we can assign the cookie j to the child i,
    and the child i will be content
            .Your goal is to maximize the number of your
                content children and output the maximum number.

        Example 1 :

    Input : g = [ 1, 2, 3 ],
            s = [ 1, 1 ] Output : 1 Explanation
    : You have 3 children and
      2 cookies.The greed factors of 3 children are 1,
            2, 3. And even though you have 2 cookies,
            since their size is both 1,
            you could only make the child whose greed factor
                is 1 content.You need to output 1. Example 2 :

    Input : g = [ 1, 2 ],
            s = [ 1, 2, 3 ] Output : 2 Explanation
    : You have 2 children and
      3 cookies.The greed factors of 2 children are 1,
            2. You have 3 cookies and their sizes are big enough to gratify all
                of the children,
            You need to output 2.

#include <bits/stdc++.h>
    using namespace std;

class Solution {
public:
  // Function to find the maximum number of content students
  int findContentChildren(vector<int> &student, vector<int> &cookie) {
    // Sort both arrays to apply the greedy strategy
    sort(student.begin(), student.end());
    sort(cookie.begin(), cookie.end());

    // Initialize DP table with -1
    vector<vector<int>> memo(student.size(), vector<int>(cookie.size(), -1));

    // Start recursion from index 0 for both arrays
    return helper(0, 0, student, cookie, memo);
  }

private:
  // Recursive helper function with memoization
  int helper(int studentIndex, int cookieIndex, vector<int> &student,
             vector<int> &cookie, vector<vector<int>> &memo) {
    // Base case: if we reach end of either list
    if (studentIndex >= student.size() || cookieIndex >= cookie.size())
      return 0;

    // Return memoized result if already computed
    if (memo[studentIndex][cookieIndex] != -1)
      return memo[studentIndex][cookieIndex];

    int result = 0;

    // If the cookie satisfies the student's greed
    if (cookie[cookieIndex] >= student[studentIndex]) {
      // Option 1: assign this cookie and move to next student and cookie
      result = max(result, 1 + helper(studentIndex + 1, cookieIndex + 1,
                                      student, cookie, memo));
    }

    // Option 2: skip this cookie and try the next one for the same student
    result = max(result,
                 helper(studentIndex, cookieIndex + 1, student, cookie, memo));

    // Store the result in memo table
    return memo[studentIndex][cookieIndex] = result;
  }
};

int main() {
  vector<int> student = {1, 2, 3};
  vector<int> cookie = {1, 1};

  // Create Solution object
  Solution solver;

  // Get the number of content students and print it
  int result = solver.findContentChildren(student, cookie);
  cout << "Maximum number of content students: " << result << endl;

  return 0;
}
