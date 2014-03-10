#include "shellinford_bit_vector.h"
#include <iostream>
#include <ctime>

using namespace std;
int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      cerr << "USAGE: rank_bit_vector dicname" << endl;
    }
    srand((unsigned)time(NULL));
    shellinford::bit_vector bv;
    bv.read(argv[1]);

    uint64_t m = bv.size(true);
    uint64_t n = bv.size();
    clock_t tmp = clock();
    for (uint64_t i = 0; i < m; i++) { bv.rank(rand() % n); }
    double sec = double(clock() - tmp) / CLOCKS_PER_SEC;
    cout << sec << "s" << endl;

  } catch (const char *err) {
    cerr << "ERROR: " << err << endl;
  }
  return 0;
}

