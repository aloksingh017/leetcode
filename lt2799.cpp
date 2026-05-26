int countCompleteSubarrays(vector<int> &nums) {
  int unique = unordered_set<int>(nums.begin(), nums.end()).size();
  int left = 0, right = 0;

  unordered_map<int, int> mp;
  int cnt = 0;
  while (right < nums.size()) {
    mp[nums[right]]++;
    while (mp.size() == unique) {
      cnt += nums.size() - right;
      mp[nums[left]]--;
      if (mp[nums[left]] == 0)
        mp.erase(nums[left]);
      left++;
    }
    right++;
  }
  return cnt;
}