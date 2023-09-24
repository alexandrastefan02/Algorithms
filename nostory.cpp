/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */

#include <cstdint>

#include <fstream>

#include <vector>

#include <algorithm>

#include <utility>

#include <cstring>

using namespace std;



int64_t SolveTask1(vector < int > & a, vector < int > & b, int n) {
  int64_t sum = 0;
  for (int i = 0; i < n; i++) {
    sum += max(a[i], b[i]);
  }
  return sum;
}

int64_t SolveTask2(vector < int > & a, vector < int > & b, int moves, int n) {
  vector < long int > maxA(n);
  vector<long int> minB(n);

  for (int i = 0; i < n; i++) {
    maxA[i] = max(a[i], b[i]);
    minB[i] = min(a[i], b[i]);
  }
  sort(maxA.begin(), maxA.end());
  sort(minB.begin(), minB.end(), greater<long int>());
  int64_t sum = 0;
  for (int j = 0; j < n; j++) {
    if (moves == 0)
    break;
    if (minB[j] > maxA[j]) {
      // long int aux = a[j];
      long int aux = maxA[j];
      maxA[j] = minB[j];
      minB[j] = aux;
      moves--;
    }
  }
  for (int i = 0; i < n; i++) {
    sum += maxA[i];
  }
  return sum;
}

vector < int > ReadVector(istream & is, int size) {
  vector < int > vec(size);
    for ( auto & num : vec ) {
      is >> num;
    }
  return vec;
}

int main() {
  ifstream fin("nostory.in");
  ofstream fout("nostory.out");

  int task;
  fin >> task;

  int n, moves;
  if (task == 1) {
    fin >> n;

  } else {
    fin >> n >> moves;
  }
  vector < int > a(n);
  for (int i = 0; i < n; i++) {
    fin >> a[i];
  }
  vector < int > b(n);
  for (int i = 0; i < n; i++) {
    fin >> b[i];
  }
  if (task == 1) {
    sort(a.begin(), a.end(), greater < int > ());
    sort(b.begin(), b.end());
  }

  auto res = task == 1 ? SolveTask1(a, b, n) : SolveTask2(a, b, moves, n);
  fout << res << "\n";
  return 0;
}
