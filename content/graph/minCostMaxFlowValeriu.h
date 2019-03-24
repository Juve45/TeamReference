#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;

const int N = 205;
const int INF = 0x3f3f3f3f;
const int Source = 0;
const int Sink = N - 3;

struct edge {
  int to, flow, cost;
};

int i, dist[N], q[N], inQ[N], poz[N], from[N];
vector<int> lda[N];
vector<edge> E;

void clearNetwork() {
  E.clear();
  for(int i = 0; i < N; ++i) lda[i].clear();
}

void addEdge(int x, int y, int flow, int cost) {
  E.push_back({y, flow, cost});
  E.push_back({x, 0, -cost});
  lda[x].push_back(E.size() - 2);
  lda[y].push_back(E.size() - 1);
}

void updateFlow(int &currFlow, int &currCost, int addFlow) {
  for(int x = Sink; x != Source; x = from[x]) addFlow = min(addFlow, E[poz[x]].flow);
  for(int x = Sink; x != Source; x = from[x]) {
    currCost += addFlow * E[poz[x]].cost;
    E[poz[x]].flow -= addFlow;
    E[poz[x] ^ 1].flow += addFlow;
  }
  currFlow += addFlow;
}

pair<int, int> getMinCostMaxFlow(int limitFlow = INF) {
  int currFlow = 0, currCost = 0;

  while(currFlow < limitFlow) {
    memset(dist, INF, sizeof(dist));
    memset(inQ, 0, sizeof(inQ));

    int st = 0, dr = 1;
    q[st] = Source; inQ[Source] = 1; dist[Source] = 0;
    while(st != dr) {
      int x = q[st];
      st = (st + 1) % N;
      inQ[x] = 2;
      for(int it : lda[x]) {
        if(E[it].flow <= 0 || dist[E[it].to] <= dist[x] + E[it].cost) continue;

        dist[E[it].to] = dist[x] + E[it].cost;
        from[E[it].to] = x;

        if(inQ[E[it].to] == 0) {
          q[dr] = E[it].to;
          if(dr == N - 1) dr = 0; else ++dr;
        } else if(inQ[E[it].to] == 2) {
          if(st == 0) st = N - 1; else --st;
          q[st] = E[it].to;
        }

        inQ[E[it].to] = 1; poz[E[it].to] = it;
      }
    }

    if(dist[Sink] == INF) break;

    updateFlow(currFlow, currCost, limitFlow - currFlow);
  }

  return make_pair(currFlow, currCost);
}

int main() {

  return 0;
}