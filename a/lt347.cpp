/*
347. Top K Frequent Elements

Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

Example 1:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:
Input: nums = [1], k = 1
Output: [1]

Example 3:
Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2
Output: [1,2]

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.

*/


// heap method

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int> freq;
        for(int i=0;i<n;i++)
            freq[nums[i]]++;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        for(auto it: freq){
             pq.push({it.second, it.first});
            if(pq.size()>k)
                pq.pop();
           
        }
        vector<int> ans;
        while(!pq.empty()){
            ans.push_back(pq.top().second);
            pq.pop();
        }
        return ans;
    }
};


// bucket:

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freq;
        int n = nums.size();
        for(int i=0;i<n;i++){
            freq[nums[i]]++;
        }
        vector<vector<int>> bucket(n+1);
        for(auto it: freq){
            bucket[it.second].push_back(it.first);
        }

        vector<int> ans;
        for(int i=n;i>=1;i--){
            for(auto it: bucket[i]){
                ans.push_back(it);
                if(ans.size() ==k)
                   return ans;
            }
        }
        return ans;
    }
};