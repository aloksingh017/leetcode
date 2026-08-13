#include <bits/stdc++.h>
using namespace std;


int cal(vector<int> &weights, int cap) {
  int cnt = 1;
  int load = 0;
  for (auto it : weights) {
    if (load + it > cap) {
      cnt++;
      load = it;
    } else {
      load += it;
    }
  }
  return cnt;
}
int shipWithinDays(vector<int> &weights, int days) {
  int low = *max_element(weights.begin(), weights.end());
  int high = 0;
  for (auto it : weights) {
    high += it;
  }
  while (low <= high) {
    int mid = (low + high) / 2;
    int daysTaken = cal(weights, mid);
    if (daysTaken <= days)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return low;
}