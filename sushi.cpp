#include <iostream>

#include <algorithm>

#include <vector>

#include <map>

using namespace std;
// bool compare(const pair<int, int>& a, const pair<int, int>& b) {
//     return a.first > b.first;
// sort in descending order of the first element


int task1(int n, int m, int x, vector< int > & p, vector< vector<int>> & g) {
  vector < int > colSums(m, 0);
  // colSums.resize(m+1);
  for (int j = 0; j < m; j++) {
    // compute the sum of elements in the j-th column
    int sum = 0;
    for (int i = 0; i < n; i++) {
      sum += (int) g[i][j];
    }
    colSums[j] = sum;  // store the sum in the vector of column sums
  }

  vector < vector < int >> dp(m + 1);
  for (int i = 0; i <= m; ++i) {
    dp[i].resize(n * x + 1);
  }
  // base case
  for (int cap = 0; cap <= n * x; ++cap) {
    dp[0][cap] = 0;
  }
  // general case
  for (int i = 1; i <= m; ++i) {
    for (int cap = 0; cap <= n * x; ++cap) {
      dp[i][cap] = dp[i - 1][cap];
      if (cap - p[i - 1] >= 0) {
        int sol_aux = dp[i - 1][cap - p[i - 1]] + colSums[i - 1];
        dp[i][cap] = max(dp[i][cap], sol_aux);
      }
    }
  }
  return dp[m][n * x];
}

int task2(int n, int m, int x, vector<int > & p, vector<vector<int>> & g) {
  vector < int > colSums(m, 0);
  for (int j = 0; j < m; j++) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
      sum += (int) g[i][j];
    }
    colSums[j] = sum;  // same as for task1
  }

  vector < vector < int >> dp(m + 1, vector < int > (n * x + 1, 0));
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n * x; j++) {
      dp[i][j] = dp[i - 1][j];
      for (int k = 1; k <= min(2, j / p[i - 1]); k++) {
        if (j >= k * p[i - 1]) {
          dp[i][j] = max(dp[i][j], dp[i-1][j-k*p[i-1]] + k*colSums[i-1]);
        }
      }
    }
  }
  return dp[m][n * x];
}

int task3(int n, int m, int x, vector<int> & p, vector<vector<int>> & g) {
  vector < int > colSums(m, 0);
  for (int j = 0; j < m; j++) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
      sum += (int) g[i][j];
    }
    colSums[j] = sum;
  }

  // int dp[m+1][n*x +1][n+1]; ->reminder da segfault
vector<vector<vector<int>>> dp(m+1, vector<vector<int>>
(n*x+1, vector<int>(n+1, 0)));

  for (int cap = 0; cap <= n * x; ++cap) {
    for (int plates = 0; plates <= n; ++plates) {
      dp[0][cap][plates] = 0;
    }
  }

  for (int i = 1; i <= m; ++i) {
    for (int cap = 0; cap <= n * x; ++cap) {
      for (int plates = 0; plates <= n; ++plates) {
        dp[i][cap][plates] = dp[i - 1][cap][plates];
        if (cap - p[i - 1] >= 0 && plates > 0) {
          int limit = min(2, min(plates, cap / p[i - 1]));
          for (int k = 1; k <= limit; ++k) {
            if (cap - k * p[i - 1] >= 0) {
              int ax = dp[i-1][cap-k*p[i-1]][plates-k]+k*colSums[i-1];
              dp[i][cap][plates] = max(dp[i][cap][plates], ax);
            }
          }
        }
      }
    }
  }
  return dp[m][n * x][n];
}

int main() {
  freopen("sushi.in", "r", stdin);
  freopen("sushi.out", "w", stdout);

  int task;  // task number

  int n;  // number of friends
  int m;  // number of sushi types
  int x;  // how much each of you is willing to spend

  vector < int > prices;  // prices of each sushi type
  // the grades you and your friends gave to each sushi type
  vector < vector < int > > grades;

  cin >> task;
  cin >> n >> m >> x;

  prices.assign(m, 0);
  grades.assign(n, vector < int > (m, 0));
  // prices.resize(m+1);
  // price of each sushi
  for (int i = 0; i < m; ++i) {
    cin >> prices[i];
  }

  // each friends rankings of sushi types
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> grades[i][j];
    }
  }

  int ans = -1;

  switch (task) {
  case 1:
    ans = task1(n, m, x, prices, grades);
    break;
  case 2:
    ans = task2(n, m, x, prices, grades);
    break;
  case 3:
    ans = task3(n, m, x, prices, grades);
    break;
  default:
    cout << "wrong task number" << endl;
  }
  // vector<int> p=task1(n,m,x,prices,grades);
  // int b=n*x;

  cout << ans << endl;
  // for(int i=0; i<m; i++)
  // {
  // 	cout<<p[i]<<endl;
  // }
  return 0;
}
