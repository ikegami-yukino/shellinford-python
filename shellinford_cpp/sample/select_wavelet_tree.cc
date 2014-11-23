#include "shellinford_wavelet_tree.h"
#include <iostream>
#include <ctime>

using namespace std;
int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      cerr << "USAGE: select_wavelet_tree dicname" << endl;
    }
    srand((unsigned)time(NULL));
    shellinford::wavelet_tree<uint8_t> wt;
    wt.read(argv[1]);

    vector<uint64_t> m;
    for (uint64_t i = 0; i < 256; i++) { m.push_back(wt.size(i)); }
    uint64_t n = wt.size();
    uint64_t c = 256;
    clock_t tmp = clock();
    for (uint64_t i = 0; i < n; i++) {
      uint64_t ct = 0;
      do { ct = rand() % c; } while (m[ct] == 0);
      wt.select(rand() % m[ct], ct);
    }
    double sec = double(clock() - tmp) / CLOCKS_PER_SEC;
    cout << sec << "s" << endl;

  } catch (const char *err) {
    cerr << "ERROR: " << err << endl;
  }
  return 0;
}

