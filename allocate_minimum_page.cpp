int helper(vector<int> &arr, int page) {
  int cnt = 1;
  int reqPage = 0;
  for (int i = 0; i < arr.size(); i++) {
    if (reqPage + arr[i] <= page)
      reqPage += arr[i];
    else {
      cnt++;
      reqPage = arr[i];
    }
  }
  return cnt;
}
int findPages(vector<int> &arr, int k) {
  // code here
  if (k > arr.size())
    return -1;
  int low = *max_element(arr.begin(), arr.end());
  int high = 0;
  for (auto it : arr)
    high += it;

  while (low <= high) {
    int mid = (low + high) / 2;
    int reqStd = helper(arr, mid);
    if (reqStd > k)
      low = mid + 1;
    else
      high = mid - 1;
  }
  return low;
}