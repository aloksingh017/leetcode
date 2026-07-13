int helper(vector<int> &arr) {
  int low = 0, high = arr.size() - 1;
  int ans = arr.size();
  while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid] >= 1) {
      ans = mid;
      high = mid - 1;
    } else
      low = mid + 1;
  }
  return ans;
}
int rowWithMax1s(vector<vector<int>> &arr) {
  // code here
  int m = arr[0].size();
  int index = -1;
  int cnt_one_max = 0;

  for (int i = 0; i < arr.size(); i++) {
    int cnt_one = m - helper(arr[i]);
    if (cnt_one > cnt_one_max) {
      cnt_one_max = cnt_one;
      index = i;
    }
  }

  return index;
}
