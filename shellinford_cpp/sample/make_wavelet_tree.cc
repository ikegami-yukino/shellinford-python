#include "shellinford_wavelet_tree.h"
#include <iostream>

using namespace std;
int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      cerr << "USAGE: make_wavelet_tree dicname < filename" << endl;
    }
    uint8_t x;
    vector<uint8_t> v;
    while (cin >> x) { v.push_back(x); }

    shellinford::wavelet_tree<uint8_t> wt;
    wt.build(v);
    wt.write(argv[1]);

  } catch (const char *err) {
    cerr << "ERROR: " << err << endl;
  }
  return 0;
}

