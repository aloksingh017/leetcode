/*
2948. Make Lexicographically Smallest Array by Swapping Elements

You are given a 0-indexed array of positive integers nums and a positive integer limit.
In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.
Return the lexicographically smallest array that can be obtained by performing the operation any number of times.

An array a is lexicographically smaller than an array b if in the first position where a and b differ, array a has an element that is less than the corresponding element in b. For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index 0 and 2 < 10.

Example 1:
Input: nums = [1,5,3,9,8], limit = 2
Output: [1,3,5,8,9]
Explanation: Apply the operation 2 times:
- Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
- Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
We cannot obtain a lexicographically smaller array by applying any more operations.
Note that it may be possible to get the same result by doing different operations.

Example 2:
Input: nums = [1,7,6,18,2,1], limit = 3
Output: [1,6,7,18,1,2]
Explanation: Apply the operation 3 times:
- Swap nums[1] with nums[2]. The array becomes [1,6,7,18,2,1]
- Swap nums[0] with nums[4]. The array becomes [2,6,7,18,1,1]
- Swap nums[0] with nums[5]. The array becomes [1,6,7,18,1,2]
We cannot obtain a lexicographically smaller array by applying any more operations.

Example 3:
Input: nums = [1,7,28,19,10], limit = 3
Output: [1,7,28,19,10]
Explanation: [1,7,28,19,10] is the lexicographically smallest array we can obtain because we cannot apply the operation on any two indices.
 

Constraints:
1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
1 <= limit <= 10^9

*/

// bruteforce
 set<vector<int>> visited;
    vector<int> ans;
    int n;

    void solve(vector<int>& nums, int limit){
        if(visited.count(nums))
            return;
        visited.insert(nums);
        ans = min(ans, nums);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(abs(nums[i]-nums[j])<= limit){
                    swap(nums[i], nums[j]);
                    solve(nums,limit);
                    swap(nums[i], nums[j]);
                }
            }
        }
    }
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        n = nums.size();
        ans = nums;
        solve(nums,limit);
        return ans;
    }


    // optimal


    class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        vector<pair<int, int>> arr;

        // Store {value, original_index}
        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort according to values
        sort(arr.begin(), arr.end());

        int start = 0;

        while (start < n) {
            int end = start;

            // Find all elements belonging to the same group
            while (end + 1 < n &&
                   arr[end + 1].first - arr[end].first <= limit) {
                end++;
            }

            // Collect original indices
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                indices.push_back(arr[i].second);
            }

            // Sort indices so smaller values go to smaller indices
            sort(indices.begin(), indices.end());

            // arr[start...end] is already sorted by value
            for (int i = 0; i < indices.size(); i++) {
                nums[indices[i]] = arr[start + i].first;
            }

            start = end + 1;
        }
        return nums;
    }
};


// optimal


class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        vector<pair<int,int>> arr;
        
        for(int i=0;i<nums.size();i++){
            arr.push_back({nums[i], i});
        }

        sort(arr.begin(), arr.end());
        int n = nums.size();
        int start = 0;
        while(start<n){
            int end = start;

            while(end+1 < n && arr[end+1].first- arr[end].first <= limit)
                end++;

            vector<int> indices;
            for(int i=  start;i<=end;i++){
                indices.push_back(arr[i].second);
            }

            sort(indices.begin(), indices.end());

            for(int i=0;i<indices.size();i++){
                nums[indices[i]] = arr[start+i].first;
            }
            start = end+1;
        }
        return nums;
    }
};