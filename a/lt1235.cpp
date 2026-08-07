/*
1235. Maximum Profit in Job Scheduling
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