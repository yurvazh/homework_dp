#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int kInf = 1e9;
const int kMaxLength = 1000;

string start;
string final;

void SolveForLevel(int change, int first_length, int second_length,
                   vector<vector<vector<int>>>& dp) {
  for (int i = 0; i < first_length + 1; ++i) {
    for (int j = 0; j < second_length + 1; ++j) {
      if ((i == 0) && (j == 0)) {
        dp[i][j][change] = 0;
        continue;
      }
      if (i == 0) {
        dp[i][j][change] = (change >= j ? 0 : kInf);
        continue;
      }
      if (j == 0) {
        dp[i][j][change] = (change >= i ? 0 : kInf);
        continue;
      }
      dp[i][j][change] =
          min(dp[i - 1][j][change - 1], dp[i][j - 1][change - 1]);
      int equal = (start[i - 1] == final[j - 1]) ? 1 : 0;
      dp[i][j][change] =
          min(dp[i][j][change], dp[i - 1][j - 1][change] + 1 - equal);
      dp[i][j][change] = min(dp[i][j][change], dp[i - 1][j - 1][change - 1]);
    }
  }
}
int main() {
  cin >> start >> final;
  int first_length = start.size();
  int second_length = final.size();
  int number_of_changes;
  cin >> number_of_changes;
  vector<vector<vector<int>>> dp(
      first_length + 1,
      vector<vector<int>>(second_length + 1,
                          vector<int>(number_of_changes + 1, kInf)));
  for (int i = 0; i < first_length + 1; ++i) {
    for (int j = 0; j < second_length + 1; ++j) {
      if (i != j) {
        dp[i][j][0] = kInf;
        continue;
      }
      if (i == 0) {
        dp[i][j][0] = 0;
      } else {
        dp[i][j][0] =
            dp[i - 1][j - 1][0] + ((start[i - 1] == final[j - 1]) ? 0 : 1);
      }
    }
  }
  for (int change = 1; change <= number_of_changes; ++change) {
    SolveForLevel(change, first_length, second_length, dp);
  }
  cout << ((dp[first_length][second_length][number_of_changes] > kMaxLength)
               ? -1
               : dp[first_length][second_length][number_of_changes])
       << endl;
}
