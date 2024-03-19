#include <iostream>
#include <string>
#include <vector>

using namespace std;

int width;
int length;
long long ans = 0;

const long long kMod = 1e9 + 7;

int Bit(int mask, int number) {
  int first_result = mask % (1 << number);
  int second_result = mask % (1 << (number + 1));
  return (second_result - first_result) / (1 << number);
}

pair<int, int> GetTwoOptions(int mask) {
  int first_mask = 0;
  int second_mask = 1;
  for (int i = 1; i < width; ++i) {
    int new_bit =
        2 - (Bit(mask, i - 1) + Bit(mask, i) + Bit(first_mask, i - 1));
    if (new_bit > 1 || new_bit < 0) {
      first_mask = -1;
      break;
    }
    first_mask += (1 << i) * new_bit;
  }
  for (int i = 1; i < width; ++i) {
    int new_bit =
        2 - (Bit(mask, i - 1) + Bit(mask, i) + Bit(second_mask, i - 1));
    if (new_bit > 1 || new_bit < 0) {
      second_mask = -1;
      break;
    }
    second_mask += (1 << i) * new_bit;
  }
  return make_pair(first_mask, second_mask);
}

bool Possible(int mask, vector<char>& street) {
  for (int i = 0; i < width; ++i) {
    if ((street[i] == '-' && Bit(mask, i) == 1) ||
        (street[i] == '+' && Bit(mask, i) == 0)) {
      return false;
    }
  }
  return true;
}

int main() {
  cin >> width >> length;
  int mask = (1 << width);
  vector<vector<char>> scheme(length, vector<char>(width));
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < length; ++j) {
      cin >> scheme[j][i];
    }
  }
  vector<vector<long long>> dp(length + 1, vector<long long>(mask, 1LL));
  for (int i = 0; i < length; ++i) {
    for (int current_mask = 0; current_mask < mask; ++current_mask) {
      dp[i + 1][current_mask] = 0LL;
      if (!Possible(current_mask, scheme[i])) {
        continue;
      }
      if (i == 0) {
        dp[i + 1][current_mask] = 1;
      } else {
        pair<int, int> options = GetTwoOptions(current_mask);
        if (options.first != -1) {
          dp[i + 1][current_mask] += dp[i][options.first];
        }
        if (options.second != -1) {
          dp[i + 1][current_mask] += dp[i][options.second];
        }
        dp[i + 1][current_mask] %= kMod;
      }
      if (i == length - 1) {
        ans = (ans + dp[i + 1][current_mask]) % kMod;
      }
    }
  }
  cout << ans << endl;
}
