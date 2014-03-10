#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include "shellinford_wavelet_tree.h"

using namespace std;
using namespace shellinford;

uint64_t lf(wavelet_tree<uint8_t> &wt, uint64_t i, uint8_t c) {
  return wt.rank_less_than(wt.size(), c) + wt.rank(i, c);
}

void rbwt(const string &s, string &t) {
  wavelet_tree<uint8_t> wt;
  wt.build(s.c_str());
  t = "";
  uint8_t  c = '$';
  uint64_t i = wt.select(0, c);
  while (1) {
    i = lf(wt, i, c);
    c = wt.get(i);
    if (c == '$') { break; }
    t.insert(t.begin(), c);
  }
}

int main(int argc, char **argv) {
  string s, t;
  while (cin >> s) {
    rbwt(s, t);
    cout << t << endl;
  }
  return 0;
}

