#include <bits/stdc++.h>
using namespace std;

class CopyPasteSystem {
private:
  list<string> dll; // Doubly linked list to maintain order
  unordered_map<string, list<string>::iterator> mp; // word -> iterator

public:
  // Copy operation
  void copy(const string &word) {
    // If already exists, remove from current position
    if (mp.find(word) != mp.end()) {
      dll.erase(mp[word]);
    }

    // Insert at end (most recent)
    dll.push_back(word);
    mp[word] = prev(dll.end());
  }

  // Paste operation
  string paste(const string &word) {
    if (mp.find(word) != mp.end()) {
      return word;
    }
    return "-1";
  }

  // Utility: print current order (for debugging)
  void printState() {
    cout << "Current order: ";
    for (const auto &w : dll) {
      cout << w << " ";
    }
    cout << endl;
  }
};

int main() {
  CopyPasteSystem cps;

  // Copy operations
  cps.copy("interview");
  cps.copy("dsa");
  cps.copy("a");
  cps.printState();
  // Expected: interview dsa a

  // Copy "interview" again → should move to end
  cps.copy("interview");
  cps.printState();
  // Expected: dsa a interview

  // Paste tests
  cout << "Paste 'dsa': " << cps.paste("dsa") << endl;       // dsa
  cout << "Paste 'system': " << cps.paste("system") << endl; // -1

  return 0;
}