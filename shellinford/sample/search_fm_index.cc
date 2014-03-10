#include "shellinford_fm_index.h"
#include <iostream>

using namespace std;
int main(int argc, char **argv) {
  try {
    if (argc < 2) {
      cerr << "USAGE: search_fm_index dicname [mode(t/m)] [eval(y/n)]" << endl;
    }
    bool use_wavelet_tree = false;
    if (argc >= 3 && argv[2][0] == 't') {
      use_wavelet_tree = true;
    }
    bool is_eval = false;
    if (argc >= 4 && argv[3][0] == 'y') {
      is_eval = true;
    }
    shellinford::fm_index fm(use_wavelet_tree);
    fm.read(argv[1]);

    string key = "";
    while (cin >> key) {
      map<uint64_t, uint64_t> dids;
      fm.search(key, dids);
      if (is_eval == false) {
        cout << dids.size() << " hits." << endl;
        map<uint64_t, uint64_t>::const_iterator i = dids.begin();
        map<uint64_t, uint64_t>::const_iterator e = dids.end();
        while (i != e) {
          cout << "[" << i->first << "]: "
               << fm.get_document(i->first)
               << "(" << i->second << ")" << endl;
          i++;
        }
        cout << endl;
      }
    }
  } catch (const char *err) {
    cerr << "ERROR: " << err << endl;
  }
  return 0;
}

