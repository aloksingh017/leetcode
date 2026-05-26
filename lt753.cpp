#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int lb(vector<int> &temp, int k) {
    int low = 0, high = temp.size() - 1;
    int ind = -1;
    while (low <= high) {
      int mid = (low + high) / 2;
      if (temp[mid] >= k) {
        ind = mid;
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }
    return ind;
  }
  int lis(vector<int> &arr) {
    // code here
    vector<int> temp;
    temp.push_back(arr[0]);

    for (int i = 1; i < arr.size(); i++) {
      if (arr[i] > temp.back())
        temp.push_back(arr[i]);
      else {
        int ind = lb(temp, arr[i]);
        temp[ind] = arr[i];
      }
    }
    return temp.size();
  }
};