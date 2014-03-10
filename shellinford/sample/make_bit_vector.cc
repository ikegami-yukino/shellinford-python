#include "shellinford_bit_vector.h"
#include <iostream>

using namespace std;
int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      cerr << "USAGE: make_bit_vector dicname < filename" << endl;
    }
    shellinford::bit_vector bv;
    uint64_t x;
    while (cin >> x) { bv.set(x); }
    bv.build();
    bv.write(argv[1]);

  } catch (const char *err) {
    cerr << "ERROR: " << err << endl;
  }
  return 0;
}

