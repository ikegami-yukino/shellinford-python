#include "shellinford_fm_index.h"
#include <iostream>

using namespace std;
int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      cerr << "USAGE: make_fm_index dicname [mode(t/m)] < filename" << endl;
    }
    bool use_wavelet_tree = false;
    if (argc >= 3 && argv[2][0] == 't') {
      use_wavelet_tree = true;
    }
    shellinford::fm_index fm(use_wavelet_tree);
    string s;
    while (getline(cin, s)) { fm.push_back(s); }

    fm.build();
    fm.write(argv[1]);
  } catch (const char *err) {
    cerr << "ERROR: " << err << endl;
  }
  return 0;
}

