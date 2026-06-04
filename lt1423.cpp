#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxScore(vector<int> &cardPoints, int k) {
    int lsum = 0;
    for (int i = 0; i < k; i++)
      lsum += cardPoints[i];

    int ans = lsum;
    int rsum = 0;
    int right = cardPoints.size() - 1;

    for (int left = k - 1; left >= 0; left--) {
      lsum -= cardPoints[left];
      rsum += cardPoints[right];
      ans = max(ans, lsum + rsum);
      right--;
    }
    return ans;
  }
};