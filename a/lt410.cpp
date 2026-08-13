/*
410. Split Array Largest Sum

Given an array nums which consists of non-negative integers and an integer k, you can split this array into k non-empty continuous subarrays.

Write an algorithm to minimize the largest sum among these k subarrays.

Example 1:

Input: nums = [7,2,5,10,8], k = 2
Output: 18
Explanation:
There are four ways to split nums in two subarrays.
The best way is to split it into [7,2,5] and [10,8], such that the largest sum is only 18.

Example 2:

Input: nums = [1,2,3,4,5], k = 2
Output: 9
 
Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 10^6
1 <= k <= min(50, nums.length)
*/

class Solution {
public:
    bool canSplit(vector<int>& nums, int k, int maxsum){
        int parts =1;
        int sum =0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]+sum > maxsum){
                parts++;
                sum= nums[i];
                if(parts>k)
                    return false;
            }else{
                sum += nums[i];
            }
        }
        return true;
    }
    int splitArray(vector<int>& nums, int k) {
        int low = *max_element(nums.begin(), nums.end());
        int high = 0;
        int n = nums.size();
        for(int i=0;i<n;i++){
            high += nums[i];
        }
        while(low<=high){
            int mid = (low+high)/2;
            if(canSplit(nums, k, mid)){
                high = mid-1;
            }
            else
                low= mid+1;
        }
        return low;
    }
};