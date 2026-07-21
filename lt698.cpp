/*
698. Partition to K Equal Sum Subsets
Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.


Example 1:

Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
Example 2:

Input: nums = [1,2,3,4], k = 3
Output: false


Constraints:

1 <= k <= nums.length <= 16
1 <= nums[i] <= 104
The frequency of each element is in the range [1, 4].


Final Complexity
Time: O(nlogn+k⋅2^n)≈O(k⋅2^n)

Space: 
O(n)
	​

*/


class Solution {
public:
    int target;
    bool solve(int i,int k,int subsetsum, vector<int>& nums,vector<bool>& used){
        if(k==0) return true;
        if(subsetsum==target)
           return  solve(0,k-1,0,nums,used);
        for(int j=i;j<nums.size();j++){
            if(used[j] || subsetsum+nums[j]>target){
                continue;
            }
            used[j]=true;
            if(solve(j+1,k,subsetsum+nums[j],nums, used)) return true;
            used[j]=false;
        }
        return false;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum=0;
        for(auto it:nums) sum+= it;
        if(sum%k != 0) return false;

        target= sum/k;
        vector<bool> used(nums.size(),false);
        sort(nums.rbegin(),nums.rend());
        return solve(0,k,0,nums,used);
    }
};