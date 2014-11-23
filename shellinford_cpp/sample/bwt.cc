#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

struct less_char {
  bool operator() (const char *l, const char *r) {
    return strcmp(l, r) < 0;
  }
};

void bwt(const string &s, string &t) {
  const char *p = s.c_str();
  t = "";

  vector<const char *> v;
  while (*p != '\0') { v.push_back(p); p++; }
  sort(v.begin(), v.end(), less_char());

  vector<const char *>::iterator i = v.begin();
  vector<const char *>::iterator e = v.end();
  while (i != e) {
    t += s[((*i - s.c_str()) + v.size() - 1) % v.size()];
    i++;
  }
}

int main(int argc, char **argv) {
  string s, t;
  while (cin >> s) {
    s += '$';
    bwt(s, t);
    cout << t << endl;
  }
  return 0;
}

