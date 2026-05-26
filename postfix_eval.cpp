class Solution {
public:
  int evaluatePostfix(vector<string> &arr) {
    // code here
    stack<int> st;
    for (int i = 0; i < arr.size(); i++) {
      if (arr[i].back() >= '0' and arr[i].back() <= '9') {
        st.push(stoi(arr[i]));
      } else {
        int n2 = st.top();
        st.pop();
        int n1 = st.top();
        st.pop();

        if (arr[i] == "+") {
          st.push(n1 + n2);
        } else if (arr[i] == "-") {
          st.push(n1 - n2);
        } else if (arr[i] == "*") {
          st.push(n1 * n2);
        } else if (arr[i] == "^") {
          st.push(pow(n1, n2));
        } else {
          st.push(floor((1.0 * n1) / n2));
        }
      }
    }

    return st.top();
  }
};