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

const int N = 100005;

int rs[N];
bool viz[N];
vector<int> lda[N], ldat[N], order;

void addEdge(int x, int y) {
  x = x < 0 ? -2 * x - 1 : 2 * x - 2;
  y = y < 0 ? -2 * y - 1 : 2 * y - 2;
  lda[x ^ 1].push_back(y);
  lda[y ^ 1].push_back(x);
  ldat[y].push_back(x ^ 1);
  ldat[x].push_back(y ^ 1);
}

void dfs1(int x) {
  viz[x] = 1;
  for(auto to : lda[x]) if(!viz[to]) dfs1(to);
  order.push_back(x);
}

void dfs2(int x) {
  if(rs[x]) puts("NO"), exit(0);
  viz[x] = 0; rs[x ^ 1] = 1;
  for(auto to : ldat[x]) if(viz[to]) dfs2(to);
}

void solve2SAT() {
  for(int i = 0; i < N; ++i) if(!viz[i]) dfs1(i);
  reverse(order.begin(), order.end());
  for(auto it : order) if(viz[it] && viz[it ^ 1]) dfs2(it);
}

int main() {
  return 0;
}