#include <iostream>

#include <vector>

#include <cstring>

using namespace std;

const int mod = 1000000007;
int type1(int x, int y) {
  vector < vector < int >> dp(x + 1, vector < int > (y + 1));
  // int dp[x+1][y+1];
  // initialize the first row and column with 1's
  for (int i = 0; i <= x; i++) dp[i][0] = 1;
  for (int j = 0; j <= y; j++) dp[0][j] = 1;
  // fill the rest of the dp table
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      // if the last digit is a 0, we can add a 0 or a 1 to the string
      if (j == 0) dp[i][j] = dp[i - 1][j] + dp[i - 1][j + 1];
      // if the last digit is a 1, we can only add a 0 to the string
      else
      dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
    }
  }
  // the answer is the sum of the last two entries
  // in the last row of the dp table
  return dp[x][y - 1] + dp[x][y];
}

long long countBinaryStrings(long long x, long long y) {
  // Initialize dp array
  // int dp[x+1][y+1];
  // memset(dp, 0, sizeof(dp));
  vector < vector < long long >> dp(x + 1, vector < long long > (y + 1, 0));

  // Initialize base cases
  for (int i = 0; i <= x; i++) {
    dp[i][0] = 1;
  }

  dp[0][1] = 1;

  // Compute dp array
  for (int i = 1; i <= x; i++) {
    for (int j = 1; j <= y; j++) {
      dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;
    }
  }

  // The answer is the sum of the last two entries in the dp array
  return dp[x][y];
}

int type2(int x, int y) {
  vector < vector < long long >> dp(x + 1, vector < long long > (y + 1, 0));
  // Initialize base cases
  for (int i = 0; i <= x; i++) {
    dp[i][0] = 1;
  }
  for (int i = 0; i <= x; i++) {
    dp[i][1] = i + 1;
  }

  dp[0][1] = 1;
  dp[0][2] = 1;
  // Compute dp array
  for (int i = 1; i <= x; i++) {
    for (int j = 2; j <= y; j++) {
      dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] + dp[i - 1][j - 2]) % mod;
    }
  }
  // The answer is the sum of the last two entries in the dp array
  return dp[x][y];
}

int main() {
  freopen("semnale.in", "r", stdin);
  freopen("semnale.out", "w", stdout);

  int sig_type, x, y;

  cin >> sig_type >> x >> y;

  switch (sig_type) {
  case 1:
    cout << countBinaryStrings(x, y);;
    break;
  case 2:
    cout << type2(x, y);
    break;
  default:
    cout << "wrong task number" << endl;
  }

  return 0;
}
