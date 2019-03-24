/**
 * Author: Djok
 * Date: 2020-01-01
 * License: CC0
 * Source: My head
 * Description: None
 * Usage: ask Djok
 * Status: tested I guess
 */

 #pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

struct lol {
  int x, y, poz;

  bool operator < (const lol &b) const {
    if(x == b.x) return y < b.y;
    return x < b.x;
  }
};

int i, j, sa[20][N], n;
lol b[N];
string s;

int main() {
  cin >> s; n = s.size();
  for(i = 1; i <= n; ++i) sa[0][i] = s[i - 1];

  for(i = 1; (1 << i) <= n; ++i) {
    for(j = 1; j <= n; ++j) {
      b[j].x = sa[i - 1][j];
      b[j].poz = j;
      if(j + (1 << (i - 1)) <= n) b[j].y = sa[i - 1][j + (1 << i)];
      else b[j].y = -1;
    }

    sort(b + 1, b + n + 1);

    for(j = 1; j <= n; ++j)
      if(b[j].x != b[j - 1].x || b[j].y != b[j - 1].y) sa[i][b[j].poz] = j;
      else sa[i][b[j].poz] = sa[i][b[j - 1].poz];
  }

  for(int k = 1; k <= n; ++k) cerr << sa[i - 1][k] << '\n';

  return 0;
}