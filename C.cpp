#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int kInf = 1e9;
const int kLog = 20;

int main() {
  int num;
  int hel;
  cin >> num >> hel;
  if (hel > kLog) {
    int cnt = 0;
    int left_border = 0;
    int right_border = num;
    while (left_border + 1 < right_border) {
      int mid = (left_border + right_border) / 2;
      if (right_border - mid > mid - left_border) {
        left_border = mid;
      } else {
        right_border = mid;
      }
      ++cnt;
    }
    cout << cnt << '\n';
    return 0;
  }
  if (num == 1) {
    cout << 0 << '\n';
    return 0;
  }
  if (hel == 0) {
    cout << -1 << '\n';
    return 0;
  }
  vector<vector<int>> dp(num + 1, vector<int>(hel + 1, kInf));
  vector<vector<int>> last(num + 1, vector<int>(hel + 1, 0));
  for (int i = 0; i < hel + 1; ++i) {
    dp[0][i] = 0;
    dp[1][i] = 0;
    dp[2][i] = 1;
    last[2][i] = 1;
  }
  dp[2][0] = kInf;
  for (int i = 3; i <= num; ++i) {
    for (int j = 1; j <= hel; ++j) {
      int last_floor = last[i - 1][j];
      last[i][j] = last_floor;
      dp[i][j] = 1 + max(dp[last_floor][j - 1], dp[i - last_floor][j]);
      if (1 + max(dp[last_floor + 1][j - 1], dp[i - last_floor - 1][j]) <=
          dp[i][j]) {
        ++last[i][j];
        dp[i][j] =
            1 + max(dp[last_floor + 1][j - 1], dp[i - last_floor - 1][j]);
      }
    }
  }
  cout << dp[num][hel] << '\n';
}
