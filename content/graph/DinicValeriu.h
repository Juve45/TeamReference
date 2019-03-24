#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int INF = 0x3f3f3f3f;
const int Source = 0;
const int Sink = N - 2;

struct edge {
  int to, flow;
};

int i, ptr[N], dist[N], q[N];
vector<int> lda[N];
vector<edge> E;

void clearNetwork() {
  E.clear();
  for(int i = 0; i < N; ++i) lda[i].clear();
}

void addEdge(int x, int y, int flow) {
  E.push_back({y, flow});
  E.push_back({x, 0});
  lda[x].push_back(E.size() - 2);
  lda[y].push_back(E.size() - 1);
}

bool bfs() {
  int st = 0, dr = 0;
  memset(dist, INF, sizeof(dist));
  for(q[st] = Source, dist[Source] = 0; st <= dr; ++st)
    for(int it : lda[q[st]])
      if(E[it].flow && dist[E[it].to] > dist[q[st]] + 1) {
        dist[E[it].to] = dist[q[st]] + 1;
        q[++dr] = E[it].to;
      }
  return dist[Sink] != INF;
}

int dfs(int x, int flow) {
  if(!flow || x == Sink) return flow;
  for(; ptr[x] < lda[x].size(); ++ptr[x]) {
    int it = lda[x][ptr[x]];
    if(E[it].flow <= 0 || dist[E[it].to] != dist[x] + 1) continue;
    int pushed = dfs(E[it].to, min(flow, E[it].flow));
    if(pushed) {
      E[it].flow -= pushed;
      E[it ^ 1].flow += pushed;
      return pushed;
    }
  }
  return 0;
}

int dinic() {
  int flow = 0;
  while(bfs()) {
    memset(ptr, 0, sizeof(ptr));
    while(int pushed = dfs(Source, INF)) flow += pushed;
  }
  return flow;
}

int main() {

  return 0;
}