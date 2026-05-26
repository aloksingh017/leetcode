#define psi pair<int, string>
class Solution {
public:
  class custom {
  public:
    bool operator()(psi p1, psi p2) {
      if (p1.first == p2.first)
        return p1.second < p2.second;
      return p1.first > p1.first;
    }
  };
  vector<string> topKFrequent(vector<string> &words, int k) {
    unordered_map<string, int> freq;
    for (int i = 0; i < words.size(); i++) {
      freq[words[i]]++;
    }

    priority_queue<psi, vector<psi>, custom> pq;
    for (auto it : freq) {
      pq.push({it.second, it.first});
      if (pq.size() > k)
        pq.pop();
    }
    vector<string> ans(k);
    int m = k - 1;
    while (!pq.empty()) {
      ans[m--] = pq.top().second;
      pq.pop();
    }
    return ans;
  }
};

#define psi pair<int, string>
class Solution {
public:
  class Custom {
  public:
    bool operator()(psi p1, psi p2) {
      if (p1.first == p2.first)
        return p1.second < p2.second;
      return p1.first > p2.first;
    }
  };
  vector<string> topKFrequent(vector<string> &words, int k) {
    unordered_map<string, int> freq;
    for (int i = 0; i < words.size(); i++) {
      freq[words[i]]++;
    }
    priority_queue<psi, vector<psi>, Custom> pq;

    for (auto it : freq) {
      pq.push({it.second, it.first});
      if (pq.size() > k)
        pq.pop();
    }
    vector<string> ans(k);
    int m = k - 1;
    while (!pq.empty()) {
      ans[m--] = pq.top().second;
      pq.pop();
    }
    return ans;
  }
};