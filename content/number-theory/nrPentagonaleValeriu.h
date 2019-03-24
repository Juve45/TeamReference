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

const int MOD = 999123;
const int N = 500005;

int i, j, p[N];

int main() {
  p[0] = 1;
  for(i = 1; i < N; ++i) {
    for(j = 1; j * (3 * j - 1) / 2 <= i; ++j) 
      if(j & 1) p[i] = (p[i] + p[i - j * (3 * j - 1) / 2]) % MOD;
      else p[i] = (p[i] - p[i - j * (3 * j - 1) / 2] + MOD) % MOD;
    for(j = 1; j * (3 * j + 1) / 2 <= i; ++j)
      if(j & 1) p[i] = (p[i] + p[i - j * (3 * j + 1) / 2]) % MOD;
      else p[i] = (p[i] - p[i - j * (3 * j + 1) / 2] + MOD) % MOD;
  }
  return 0;
}