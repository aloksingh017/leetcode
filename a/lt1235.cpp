/*
1235. Maximum Profit in Job Scheduling

We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

Example 1:
Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job. 
Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

*/


// Bruteforce


class Solution {
public:

    vector<vector<int>> jobs;
    int n;

    int solve(int i){

        if(i==n)
            return 0;

        // Skip
        int skip = solve(i+1);

        // Find next compatible job
        int next = i+1;

        while(next<n && jobs[next][0] < jobs[i][1])
            next++;

        // Take
        int take = jobs[i][2] + solve(next);

        return max(skip,take);
    }

    int jobScheduling(vector<int>& startTime,
                      vector<int>& endTime,
                      vector<int>& profit) {

        n = startTime.size();

        for(int i=0;i<n;i++)
            jobs.push_back({startTime[i],endTime[i],profit[i]});

        sort(jobs.begin(),jobs.end());

        return solve(0);
    }
};


// Memoization 

class Solution {
public:
    int solve(int i, int& n, vector<vector<int>>& jobs, vector<int>& dp){
        if(i==n)
            return 0;
        if(dp[i]!=-1)
            return dp[i];

        int skip = solve(i+1, n, jobs,dp);
        int next = i+1;
        while(next<n && jobs[next][0]< jobs[i][1]){
            next++;
        }

        int take = jobs[i][2]+ solve(next, n, jobs, dp);
        return dp[i]= max(skip, take);
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<vector<int>> jobs;
        int n = startTime.size();
        vector<int> dp(n,-1);
        for(int i=0;i<n;i++){
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());
        return solve(0, n, jobs, dp);
    }
};

// OPtimized

class Solution {
public:
    int n;
    int solve(int i,vector<vector<int>>& jobs, vector<int>& dp){
        if(i==n)
            return 0;
        if(dp[i]!=-1)
            return dp[i];
        int skip = solve(i+1, jobs,dp);
        int next = n;
        int low = i+1;
        int high = n-1;
        int end = jobs[i][1];
        while(low <= high){
            int mid = (low+high)/2;
            if(jobs[mid][0]>=end){
                next = mid;
                high = mid-1;
            }
            else
                low= mid+1;
        }
        while(next<n && jobs[next][0]< jobs[i][1])
            next++;
        int take = jobs[i][2]+ solve(next,jobs,dp);
        return dp[i] = max(skip, take);
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        n = startTime.size();
        vector<int> dp(n,-1);
        vector<vector<int>> jobs;
        for(int i=0;i<n;i++){
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());
        return solve(0,jobs, dp);
    } 
};