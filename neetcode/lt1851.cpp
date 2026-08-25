/*
1851. Minimum Interval to Include Each Query

You are given a 2D integer array intervals, where intervals[i] = [lefti, righti] describes the ith interval starting at lefti and ending at righti (inclusive). 
The size of an interval is defined as the number of integers it contains, or more formally righti - lefti + 1.

You are also given an integer array queries. The answer to the jth query is the size of the smallest interval i such that lefti <= queries[j] <= righti. 
If no such interval exists, the answer is -1.

Return an array containing the answers to the queries.

Example 1:

Input: intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
Output: [3,3,1,4]
Explanation: The queries are processed as follows:
- Query = 2: The interval [2,4] is the smallest interval containing 2. The answer is 4 - 2 + 1 = 3.
- Query = 3: The interval [2,4] is the smallest interval containing 3. The answer is 4 - 2 + 1 = 3.
- Query = 4: The interval [4,4] is the smallest interval containing 4. The answer is 4 - 4 + 1 = 1.
- Query = 5: The interval [3,6] is the smallest interval containing 5. The answer is 6 - 3 + 1 = 4.
Example 2:

Input: intervals = [[2,3],[2,5],[1,8],[20,25]], queries = [2,19,5,22]
Output: [2,-1,4,6]
Explanation: The queries are processed as follows:
- Query = 2: The interval [2,3] is the smallest interval containing 2. The answer is 3 - 2 + 1 = 2.
- Query = 19: None of the intervals contain 19. The answer is -1.
- Query = 5: The interval [2,5] is the smallest interval containing 5. The answer is 5 - 2 + 1 = 4.
- Query = 22: The interval [20,25] is the smallest interval containing 22. The answer is 25 - 20 + 1 = 6.
 

Constraints:

1 <= intervals.length <= 10^5
1 <= queries.length <= 10^5
intervals[i].length == 2
1 <= lefti <= righti <= 10^7
1 <= queries[j] <= 10^7
 

*/

// Bruteforce

    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> ans;
        for(int query: queries){
            int minSize = INT_MAX;
            for(auto interval: intervals){
                int left = interval[0];
                int right = interval[1];
                if(left <= query && query<= right){
                    int size = right-left+1;
                    minSize = min(minSize, size);
                }
            }
            if(minSize == INT_MAX)
                ans.push_back(-1);
            else
                ans.push_back(minSize);
        }
        return ans;
    }


    // efficient solution
    // Time Complexity:  O(N log N + Q log Q)
    // Space Complexity: O(N + Q)


class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals,
                             vector<int>& queries) {

        // Sort intervals by left endpoint
        sort(intervals.begin(), intervals.end());

        // Store {query, original index}
        vector<pair<int, int>> qs;

        for (int i = 0; i < queries.size(); i++) {
            qs.push_back({queries[i], i});
        }

        // Sort queries
        sort(qs.begin(), qs.end());

        vector<int> ans(queries.size(), -1);

        // {interval size, right endpoint}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        int i = 0;

        for (auto [query, index] : qs) {

            // Add all intervals whose left <= query
            while (i < intervals.size() && intervals[i][0] <= query) {

                int left = intervals[i][0];
                int right = intervals[i][1];

                int size = right - left + 1;

                pq.push({size, right});

                i++;
            }

            // Remove intervals that cannot contain query
            while (!pq.empty() && pq.top().second < query) {
                pq.pop();
            }

            // Smallest valid interval
            if (!pq.empty()) {
                ans[index] = pq.top().first;
            }
        }

        return ans;
    }
};
