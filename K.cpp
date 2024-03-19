#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  int num;
  int stamina;
  cin >> num >> stamina;
  vector<int> complexity(num);
  vector<int> cost(num);
  for (int i = 0; i < num; ++i) {
    cin >> complexity[i];
  }
  for (int i = 0; i < num; ++i) {
    cin >> cost[i];
  }
  vector<vector<int>> dp(num + 1, vector<int>(stamina + 1, 0));
  vector<vector<bool>> take(num + 1, vector<bool>(stamina + 1, false));
  for (int i = 1; i <= num; ++i) {
    for (int j = 1; j <= stamina; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= complexity[i - 1] &&
          (dp[i - 1][j - complexity[i - 1]] + cost[i - 1] > dp[i][j])) {
        dp[i][j] = dp[i - 1][j - complexity[i - 1]] + cost[i - 1];
        take[i][j] = true;
      }
    }
  }
  int current_sum = stamina;
  stack<int> answer;
  for (int i = num; i >= 1; --i) {
    if (take[i][current_sum]) {
      answer.push(i);
      current_sum -= complexity[i - 1];
    }
  }
  while (!answer.empty()) {
    cout << answer.top() << '\n';
    answer.pop();
  }
}
