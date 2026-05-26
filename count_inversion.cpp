#include <bits/stdc++.h>
using namespace std;
int merge(vector<int> &arr, int low, int mid, int high) {
  vector<int> temp;
  int left = low;
  int right = mid + 1;
  int cnt = 0;
  while (left <= mid && right <= high) {
    if (arr[left] <= arr[right]) {
      temp.push_back(arr[left]);
      left++;
    } else {
      cnt += mid - left + 1;
      temp.push_back(arr[right]);
      right++;
    }
  }
  while (left <= mid) {
    temp.push_back(arr[left]);
    left++;
  }
  while (right <= high) {
    temp.push_back(arr[right]);
    right++;
  }
  for (int i = low; i <= high; i++) {
    arr[i] = temp[i - low];
  }
  return cnt;
}
int mergesort(vector<int> &arr, int low, int high) {
  int cnt = 0;
  if (low >= high)
    return cnt;
  int mid = (low + high) / 2;
  cnt += mergesort(arr, low, mid);
  cnt += mergesort(arr, mid + 1, high);
  cnt += merge(arr, 0, mid, high);
  return cnt;
}
int count_inversion(vector<int> &arr) {
  return mergesort(arr, 0, arr.size() - 1);
}
int main() {
  vector<int> arr = {5, 4, 3, 2, 1};
  int ans = count_inversion(arr);
  cout << ans;
  return 0;
}