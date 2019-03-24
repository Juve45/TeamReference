/**
 * Author: Djok
 * Date: 2020-01-01
 * License: CC0
 * Source: My head
 * Description: None
 * Usage: ask Djok
 * Status: tested I guess
 */

typedef unsigned long long ull;

const int N = 100005;
const int P = 239017;

string s;
ull h[N], deg[N];

void init() {
  int n = s.size();
  deg[0] = 1; h[0] = 0;
  for(int i = 0; i < n; ++i) {
    h[i + 1] = h[i] * P + s[i];
    deg[i + 1] = deg[i] * P;
  }
}

ull getHash(int i, int len) {
  return h[i + len] - h[i] * deg[len];
}
