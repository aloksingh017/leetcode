int target = 0;
    bool backtrack(int i, int k,  int subsetSum, vector<bool>& used, vector<int>& nums) {
        // all subsets formed
        if (k == 0)
            return true;
        // one subset completed
        if (subsetSum == target)
            return backtrack(0, k - 1, 0, used, nums);
        for (int j = i; j < nums.size(); j++) {
            if (used[j] || subsetSum + nums[j] > target)
                continue;
            used[j] = true;
            if (backtrack(j + 1,k,subsetSum + nums[j], used,nums)) return true;
            used[j] = false;
        }
        return false;
    }

    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        int sum = 0;
        for (int x : nums) sum += x;

        if (sum % k) return false;
        target = sum / k;

        sort(nums.rbegin(), nums.rend()); // optimization
        vector<bool> used(n, false);
        return backtrack(0, k, 0, used, nums);
    }