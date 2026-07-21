/*

752. Open the Lock
You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'.
The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

The lock initially starts at '0000', a string representing the state of the 4 wheels.

You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

Example 1:
Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation: 
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".
Example 2:

Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation: We can turn the last wheel in reverse to move from "0000" -> "0009".
Example 3:

Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation: We cannot reach the target without getting stuck.
 

Constraints:

1 <= deadends.length <= 500
deadends[i].length == 4
target.length == 4
target will not be in the list deadends.
target and deadends[i] consist of digits only.


Complexity

There are at most:

10 × 10 × 10 × 10 = 10000

possible lock states.

Each state has 8 neighbors.

So:

Time: O(10000×8), which is effectively O(1) because the state space is fixed.
Space: O(10000) for the queue and visited set.
*/

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {

        unordered_set<string> dead(deadends.begin(), deadends.end());

        if (dead.count("0000"))
            return -1;

        queue<string> q;
        unordered_set<string> vis;

        q.push("0000");
        vis.insert("0000");

        int moves = 0;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                string cur = q.front();
                q.pop();

                if (cur == target)
                    return moves;

                for (int i = 0; i < 4; i++) {

                    string up = cur;
                    string down = cur;

                    up[i] = (up[i] == '9') ? '0' : up[i] + 1;
                    down[i] = (down[i] == '0') ? '9' : down[i] - 1;

                    if (!dead.count(up) && !vis.count(up)) {
                        vis.insert(up);
                        q.push(up);
                    }

                    if (!dead.count(down) && !vis.count(down)) {
                        vis.insert(down);
                        q.push(down);
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};



// bidirectional search

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> dead(deadends.begin(), deadends.end());

        if (dead.count("0000"))
            return -1;

        if (target == "0000")
            return 0;

        unordered_set<string> beginSet, endSet, visited;

        beginSet.insert("0000");
        endSet.insert(target);
        visited.insert("0000");
        visited.insert(target);

        int moves = 0;

        while (!beginSet.empty() && !endSet.empty()) {

            // Always expand the smaller frontier
            if (beginSet.size() > endSet.size())
                swap(beginSet, endSet);

            unordered_set<string> nextLevel;

            for (string cur : beginSet) {

                if (dead.count(cur))
                    continue;

                if (endSet.count(cur))
                    return moves;

                for (int i = 0; i < 4; i++) {

                    char original = cur[i];

                    // Rotate up
                    cur[i] = (original == '9') ? '0' : original + 1;

                    if (!dead.count(cur)) {
                        if (endSet.count(cur))
                            return moves + 1;

                        if (!visited.count(cur)) {
                            visited.insert(cur);
                            nextLevel.insert(cur);
                        }
                    }

                    // Rotate down
                    cur[i] = (original == '0') ? '9' : original - 1;

                    if (!dead.count(cur)) {
                        if (endSet.count(cur))
                            return moves + 1;

                        if (!visited.count(cur)) {
                            visited.insert(cur);
                            nextLevel.insert(cur);
                        }
                    }

                    // Restore
                    cur[i] = original;
                }
            }

            beginSet = nextLevel;
            moves++;
        }

        return -1;
    }
};