#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const int kInf = 2'147'483'647;

int main() {
  int len;
  cin >> len;
  vector<int> sequence(len);
  for (int i = 0; i < len; ++i) {
    cin >> sequence[i];
  }
  vector<int> previous_element(len, -1);
  vector<pair<int, int>> dp(len + 1, make_pair(-kInf, -1));
  dp[0] = make_pair(kInf, -1);
  int ans = 0;
  for (int i = 0; i < len; ++i) {
    int lhs = 0;
    int rhs = len;
    while (lhs + 1 < rhs) {
      int mid = (lhs + rhs) / 2;
      if (dp[mid].first >= sequence[i]) {
        lhs = mid;
      } else {
        rhs = mid;
      }
    }
    previous_element[i] = dp[lhs].second;
    ans = max(ans, rhs);
    dp[rhs] = max(dp[rhs], make_pair(sequence[i], i));
  }
  cout << ans << endl;
  stack<int> full_answer;
  full_answer.push(dp[ans].second);
  while (--ans > 0) {
    full_answer.push(previous_element[full_answer.top()]);
  }
  while (!full_answer.empty()) {
    cout << full_answer.top() + 1 << ' ';
    full_answer.pop();
  }
  cout << endl;
}
