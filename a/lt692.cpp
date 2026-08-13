/*
692. Top K Frequent Words
Given an array of strings words and an integer k, return the k most frequent strings.
Return the answer sorted by the frequency from highest to lowest. Sort the words with the same frequency by their lexicographical order.

Example 1:
Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" and "love" are the two most frequent words.
Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:

Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words, with the number of occurrence being 4, 3, 2 and 1 respectively.

Constraints:

1 <= words.length <= 500
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
k is in the range [1, The number of unique words[i]]
 

Follow-up: Could you solve it in O(n log(k)) time and O(n) extra space?

Time: O(n + m log k)
Space: O(m)
*/
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