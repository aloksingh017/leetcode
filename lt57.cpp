// The problem was to design four functions:
// 1. Initialize user_id, window_size, and max_request for a user.
// 2. Check if the current request for a user is allowed, based on the time
// window.
// 3. Check how many requests were approved in the last window.
// 4. Check how many requests were rejected in the last window.
// I first implemented a brute-force solution, which took O(N) time.
// Then, I optimized the solution using binary search, which was fairly
// straightforward. give me code in c++

#include <bits/stdc++.h>
using namespace std;

class RateLimiter {
private:
  struct UserData {
    long long windowSize;
    int maxRequest;

    vector<long long> approvedRequests;
    vector<long long> rejectedRequests;
  };

  unordered_map<int, UserData> users;

  int countInLastWindow(const vector<long long> &timestamps,
                        long long currentTime, long long windowSize) {
    long long windowStart = currentTime - windowSize + 1;

    auto it = lower_bound(timestamps.begin(), timestamps.end(), windowStart);

    return timestamps.end() - it;
  }

public:
  /*
      Initialize user configuration.

      userId      : unique user id
      windowSize  : time window size
      maxRequest  : maximum allowed requests in that window
  */
  void init(int userId, long long windowSize, int maxRequest) {
    users[userId] = UserData{windowSize, maxRequest, {}, {}};
  }

  /*
      Returns true if request is allowed.
      Returns false if request is rejected.
  */
  bool isAllowed(int userId, long long currentTime) {
    if (users.find(userId) == users.end()) {
      return false;
    }

    UserData &user = users[userId];

    int approvedCount =
        countInLastWindow(user.approvedRequests, currentTime, user.windowSize);

    if (approvedCount < user.maxRequest) {
      user.approvedRequests.push_back(currentTime);
      return true;
    } else {
      user.rejectedRequests.push_back(currentTime);
      return false;
    }
  }

  /*
      Number of approved requests in the last window.
  */
  int getApprovedCount(int userId, long long currentTime) {
    if (users.find(userId) == users.end()) {
      return 0;
    }

    UserData &user = users[userId];

    return countInLastWindow(user.approvedRequests, currentTime,
                             user.windowSize);
  }

  /*
      Number of rejected requests in the last window.
  */
  int getRejectedCount(int userId, long long currentTime) {
    if (users.find(userId) == users.end()) {
      return 0;
    }

    UserData &user = users[userId];

    return countInLastWindow(user.rejectedRequests, currentTime,
                             user.windowSize);
  }
};

int main() {
  RateLimiter limiter;

  limiter.init(101, 10, 3);

  cout << limiter.isAllowed(101, 1) << endl; // true
  cout << limiter.isAllowed(101, 2) << endl; // true
  cout << limiter.isAllowed(101, 3) << endl; // true
  cout << limiter.isAllowed(101, 4) << endl; // false

  cout << limiter.getApprovedCount(101, 4) << endl; // 3
  cout << limiter.getRejectedCount(101, 4) << endl; // 1

  cout << limiter.isAllowed(101, 12) << endl; // true

  cout << limiter.getApprovedCount(101, 12) << endl; // 3
  cout << limiter.getRejectedCount(101, 12) << endl; // 1

  return 0;
}