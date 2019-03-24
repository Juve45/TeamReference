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

const int N = 105;

int i, match[N], p[N], base[N], q[N];
bool used[N], viz[N], blossom[N];
vector<int> lda[N];

int lca(int a, int b) {
  memset(viz, 0, sizeof(viz));
  while(1) {
    a = base[a];
    viz[a] = 1;
    if(match[a] == -1) break;
    a = p[match[a]];
  }
  while(1) {
    b = base[b];
    if(viz[b]) break;
    b = p[match[b]];
  }
  return b;
}

void markPath(int x, int y, int children) {
  while(base[x] != y) {
    blossom[base[x]] = blossom[base[match[x]]] = 1;
    p[x] = children;
    children = match[x];
    x = p[match[x]];
  }
}

int findPath(int x) {
  memset(used, 0, sizeof(used));
  memset(p, -1, sizeof(p));
  for(int i = 0; i < N; ++i) base[i] = i;
 
  int qh = 0, qt = 0;
  q[qt++] = x; used[x] = 1;
  while(qh < qt) {
    int v = q[qh++];
    for(int to : lda[v]) {
      if(base[v] == base[to] || match[v] == to) continue;
      if(to == x || match[to] != -1 && p[match[to]] != -1) {
        int curbase = lca(v, to);
        memset(blossom, 0, sizeof(blossom));
        markPath(v, curbase, to);
        markPath(to, curbase, v);
        for(int i = 0; i < N; ++i)
          if(blossom[base[i]]) {
            base[i] = curbase;
            if(!used[i]) {
              used[i] = 1;
              q[qt++] = i;
            }
          }
      }
      else if(p[to] == -1) {
        p[to] = v;
        if(match[to] == -1) return to;
        to = match[to];
        used[to] = 1;
        q[qt++] = to;
      }
    }
  }
  return -1;
}

int main() {
  // add edge x, y and y, x to lda
  memset(match, -1, sizeof(match));
  for(i = 0; i < N; ++i)
    if(match[i] == -1)
      for(int to : lda[i])
        if(match[to] == -1) {
          match[to] = i;
          match[i] = to;
          break;
        }
  
  for(i = 0; i < N; ++i)
    if(match[i] == -1) {
      int v = findPath(i);
      while(v != -1) {
        int pv = p[v], ppv = match[pv];
        match[v] = pv; match[pv] = v; v = ppv;
      }
    }
  
  return 0;
}