/*
leetcode 1723

1723. Find Minimum Time to Finish All Jobs

You are given an integer array jobs, where jobs[i] is the time it takes to complete the ith job. 
There are k workers, and each worker can be assigned multiple jobs. 
A worker can only work on one job at a time, 
and once a job is started, it must be completed before another job can be started.

Return the minimum total time required to finish all the jobs.

Example 1:

Input: jobs = [3,2,3], k = 3
Output: 3
Explanation:
Assign each job to a different worker.

Example 2:

Input: jobs = [1,2,4,7,8], k = 2
Output: 11
Explanation:
Assign jobs to the first worker as [7,4]
and jobs to the second worker as [8,1,2]

time complexity
O(k * k^n)
*/


class Solution {
public:
    bool ispossible(int idx, vector<int>& jobs, int k, int limit, vector<int> workers){
        if(idx==jobs.size())
            return true;
        for(int i=0;i<k;i++){
            if(workers[i]+jobs[idx] > limit)
                continue;
            workers[i] += jobs[idx];
            if(ispossible(idx+1, jobs, k, limit, workers))
                return true;
            workers[i] -= jobs[idx];
            if(workers[i]==0)
                break;
        }
        return false;

    }
    int minimumTimeRequired(vector<int>& jobs, int k) {
       
        int low = *max_element(jobs.begin(), jobs.end());
        int high = 0;
        int n = jobs.size();
        for(int i=0;i<n;i++)
            high += jobs[i];
        
        while(low<=high){
            int mid = (low+high)/2;
             vector<int> workers(k,0);
             if(ispossible(0,jobs,k,mid,workers))
                high = mid-1;
            else
                low= mid+1;
        }
        return low;
    }
};