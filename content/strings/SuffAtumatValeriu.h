/**
 * Author: Djok
 * Date: 2020-01-01
 * License: CC0
 * Source: My head
 * Description: None
 * Usage: ask Djok
 * Status: tested I guess
 */

 #include <bits/stdc++.h>
// Kth lexi substring with repetitions, aaa = {a, a, a, aa, aa, aaa}
using namespace std;

const int N = 200005;
const int ALFA = 26;

struct state {
  int link, len, next[ALFA];
  long long cnt;

  state(int _link = 0, int _len = 0, long long _cnt = 0) {
    memset(next, ~0, sizeof(next));
    link = _link; len = _len; cnt = _cnt;
  }
};

int i, n, last, sz, k;
long long dp[N];
bool viz[N];
string s;
state sfa[N];
vector<int> lens[N];

void addLetter(char c) {
  int now = sz++, p = last;
  sfa[now].len = sfa[last].len + 1;
  sfa[now].cnt = 1;

  for(; p != -1 && sfa[p].next[c] == -1; p = sfa[p].link) sfa[p].next[c] = now;

  if(p == -1) sfa[now].link = 0;
  else {
    int q = sfa[p].next[c];
    if(sfa[q].len == sfa[p].len + 1) sfa[now].link = q;
    else {
      int clone = sz++;
      sfa[clone] = sfa[q];
      sfa[clone].len = sfa[p].len + 1;
      sfa[clone].cnt = 0;

      for(; p != -1 && sfa[p].next[c] == q; p = sfa[p].link) sfa[p].next[c] = clone;

      sfa[q].link = sfa[now].link = clone;
    }
  }

  last = now;
}

void dfs(int x) {
  viz[x] = 1;
  dp[x] = sfa[x].cnt;

  for(int i = 0; i < 26; ++i) {
    if(sfa[x].next[i] == -1) continue;

    if(!viz[sfa[x].next[i]]) dfs(sfa[x].next[i]);
    dp[x] += dp[sfa[x].next[i]];
  }
}

void Solve(int x, int need) {
  if(!need) return;

  if(x && sfa[x].cnt >= need) return;
  if(x) need -= sfa[x].cnt;

  for(int i = 0; i < 26 && need; ++i) {
    if(sfa[x].next[i] == -1) continue;

    if(dp[sfa[x].next[i]] < need) need -= dp[sfa[x].next[i]];
    else {
      cout << char(i + 'a');
      Solve(sfa[x].next[i], need);
      return;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);

  sz = 1; sfa[0].link = -1;

  cin >> s >> k;

  if(k > 1LL * s.size() * (s.size() + 1) / 2) return cout << "No such line.\n", 0;

  for(auto it : s) addLetter(it - 'a');

  for(i = 1; i < sz; ++i) lens[sfa[i].len].push_back(i);

  for(i = s.size(); i; --i)
    for(auto it : lens[i])
      sfa[sfa[it].link].cnt += sfa[it].cnt;

  dfs(0);

  Solve(0, k);

  return 0;
}