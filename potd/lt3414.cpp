/*
3414. Maximum Score of Non-overlapping Intervals

You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri, and has a weight of weighti. 
You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.

Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.

Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.

Example 1:
Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
Output: [2,3]
Explanation:
You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.

Example 2:
Input: intervals = [[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]
Output: [1,3,5,6]
Explanation:
You can choose the intervals with indices 1, 3, 5, and 6 with respective weights of 7, 6, 3, and 5.

Constraints:
1 <= intevals.length <= 5 * 10^4
intervals[i].length == 3
intervals[i] = [li, ri, weighti]
1 <= li <= ri <= 10^9
1 <= weighti <= 10^9
*/

class Solution {
public:
    struct Node {
        long long score;
        vector<int> indices;
    };

    // Return true if a is better than b
    bool better(const Node& a, const Node& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.indices < b.indices;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {start, end, weight, originalIndex}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by starting time
        sort(a.begin(), a.end());

        // next[i] = first interval whose start > a[i].end
        vector<int> next(n);

        for (int i = 0; i < n; i++) {
            int lo = i + 1;
            int hi = n;

            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (a[mid][0] > a[i][1])
                    hi = mid;
                else
                    lo = mid + 1;
            }

            next[i] = lo;
        }

        // dp[i][k] = best answer starting from i
        // when we can still select at most k intervals
        vector<vector<Node>> dp(n + 1, vector<Node>(5));

        // Base case: no intervals left or no selections allowed
        for (int k = 0; k <= 4; k++) {
            dp[n][k] = {0, {}};
        }

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Option 1: Skip current interval
                Node skip = dp[i + 1][k];

                // Option 2: Take current interval
                Node take = dp[next[i]][k - 1];

                take.score += a[i][2];
                take.indices.push_back((int)a[i][3]);

                // Choose better answer
                if (better(take, skip))
                    dp[i][k] = take;
                else
                    dp[i][k] = skip;
            }
        }

        vector<int> ans = dp[0][4].indices;

        // Problem asks for indices in increasing order
        sort(ans.begin(), ans.end());

        return ans;
    }
};

class Solution {
public:
    int n;
    vector<array<long long, 4>> a;
    vector<int> nxt;

    // dp[i][k] = maximum score from i with k intervals left
    vector<vector<long long>> dp;

    long long solve(int i, int k) {

        if (i == n || k == 0)
            return 0;

        if (dp[i][k] != -1)
            return dp[i][k];

        // Don't take current interval
        long long skip = solve(i + 1, k);

        // Take current interval
        long long take = a[i][2] + solve(nxt[i], k - 1);

        return dp[i][k] = max(skip, take);
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        n = intervals.size();

        // start, end, weight, original index
        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort according to start time
        sort(a.begin(), a.end());

        // Find next non-overlapping interval
        nxt.resize(n);

        for (int i = 0; i < n; i++) {

            int lo = i + 1;
            int hi = n;

            while (lo < hi) {

                int mid = lo + (hi - lo) / 2;

                if (a[mid][0] > a[i][1])
                    hi = mid;
                else
                    lo = mid + 1;
            }

            nxt[i] = lo;
        }

        // Initialize memoization table
        dp.assign(n, vector<long long>(5, -1));

        // Calculate maximum score
        solve(0, 4);

        // Reconstruct answer
        vector<int> ans;

        int i = 0;
        int k = 4;

        while (i < n && k > 0) {

            long long skip = solve(i + 1, k);

            long long take = a[i][2] + solve(nxt[i], k - 1);

            if (take >= skip) {

                ans.push_back(a[i][3]);

                i = nxt[i];
                k--;

            } else {
                i++;
            }
        }

        // Required: lexicographically smallest list
        sort(ans.begin(), ans.end());

        return ans;
    }
};