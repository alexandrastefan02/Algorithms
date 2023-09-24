#include <iostream>

#include <fstream>

#include <vector>

#include <algorithm>

#include <numeric>

using namespace std;

int main() {
  ifstream fin("feribot.in");
  ofstream fout("feribot.out");
  int N, K;
  fin >> N >> K;
  long int min = 0, max = 0;
  // fout<<"lala"<<endl;
  vector < long int > M(N);
  for (long int i = 0; i < N; i++) {
    fin >> M[i];
    max += M[i];
  }
  // long int max=accumulate(M.begin(), M.end(), 0);
  // min = *min_element(M.begin(), M.end());
  while (min <= max) {
    long int mid = (min + max) / 2;

    long int ferry_count = 0;
    long int ferry_weight = 0;
    bool valid = true;

    for (int i = 0; i < N; i++) {
      if (M[i] > mid) {
        valid = false;
        break;
      }

      switch (ferry_weight + M[i] <= mid) {
      case true:
        ferry_weight += M[i];
        break;
      case false:
        ferry_count++;
        ferry_weight = M[i];
        break;
      }
    }
    if (valid && ferry_count < K) {
      max = mid - 1;
    } else {
      min = mid + 1;
    }
  }

  fout << min << endl;
  fin.close();
  fout.close();
  return 0;
}
