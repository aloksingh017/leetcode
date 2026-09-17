/*
1477. Find Two Non-overlapping Sub-arrays Each With Target Sum

You are given an array of integers arr and an integer target.
You have to find two non-overlapping sub-arrays of arr each with a sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.

Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.

 

Example 1:
Input: arr = [3,2,2,4,3], target = 3
Output: 2
Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.

Example 2:
Input: arr = [7,3,4,7], target = 7
Output: 2
Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.

Example 3:
Input: arr = [4,3,2,6,2,3,4], target = 6
Output: -1
Explanation: We have only one sub-array of sum = 6.
 

Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 1000
1 <= target <= 10^8
*/

/*
1. Brute Force

Since we want two subarrays, we can:

Generate every possible subarray.
Store all subarrays whose sum is target.
Try every pair of valid subarrays.
Check whether they overlap.
Minimize their combined length.
*/

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        vector<pair<int, int>> subarrays;

        // Find all subarrays having sum = target
        for (int i = 0; i < n; i++) {
            int sum = 0;

            for (int j = i; j < n; j++) {
                sum += arr[j];

                if (sum == target) {
                    subarrays.push_back({i, j});
                }
            }
        }

        int ans = INT_MAX;

        // Try every pair
        for (int i = 0; i < subarrays.size(); i++) {
            for (int j = i + 1; j < subarrays.size(); j++) {

                int l1 = subarrays[i].first;
                int r1 = subarrays[i].second;

                int l2 = subarrays[j].first;
                int r2 = subarrays[j].second;

                // Non-overlapping
                if (r1 < l2 || r2 < l1) {
                    int len1 = r1 - l1 + 1;
                    int len2 = r2 - l2 + 1;

                    ans = min(ans, len1 + len2);
                }
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};


// sliding window + DP

int minSumOfLengths(vector<int>& arr, int target) {
    int n = arr.size();

    const int INF = 1e9;

    vector<int> best(n, INF);

    int left = 0;
    int sum = 0;
    int ans = INF;

    for (int right = 0; right < n; right++) {

        // Add current element
        sum += arr[right];

        // Shrink window if sum becomes too large
        while (sum > target) {
            sum -= arr[left];
            left++;
        }

        // We found a subarray [left ... right]
        if (sum == target) {

            int len = right - left + 1;

            // Find the best subarray before this one
            if (left > 0 && best[left - 1] != INF) {
                ans = min(ans, len + best[left - 1]);
            }
        }

        // Carry forward previous best
        if (right > 0) {
            best[right] = best[right - 1];
        }

        // Current subarray can be the best
        if (sum == target) {
            int len = right - left + 1;
            best[right] = min(best[right], len);
        }
    }
    return ans == INF ? -1 : ans;
}

