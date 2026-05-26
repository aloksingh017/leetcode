
class Solution {
  struct meeting {
    int start;
    int end;
    int pos;
  };

public:
  bool static cmp(struct meeting m1, struct meeting m2) {
    if (m1.end < m2.end)
      return true;
    else if (m1.end > m2.end)
      return false;
    else if (m1.pos < m2.pos)
      return true;
    return false;
  }

  int maxMeetings(int s[], int e[], int n) {
    int cnt = 1;
    struct meeting meet[n];
    for (int i = 0; i < n; i++) {
      meet[i].start = s[i];
      meet[i].end = e[i];
      meet[i].pos = i + 1;
    }

    sort(meet, meet + n, cmp);
    int lim = meet[0].end;

    for (int i = 1; i < n; i++) {
      if (meet[i].start > lim) {
        lim = meet[i].end;
        cnt++;
      }
    }

    return cnt;
  }
};