/**
 * Author: Roms
 * Date: 2019-03-24
 * License: CC0
 * Description: Computes the min-cost perfect matching of a graph, |L|=|R|=n
 * Time: $O(n^3)$
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 505;
const long long INF = 1e18;

int n;
long long a[N][N]; // a[1..n][1..n], a[i][j] = cost(i, j)
long long u[N], v[N];
int p[N], way[N];

int main(){
  long long res = 0;
  for(int i = 1; i <= n; ++i){
    p[0] = i;
    int j0 = 0;
    vector<long long> minv (n + 1, INF);
    vector<char> used (n + 1, false);
    do{
      used[j0] = true;
      int i0 = p[j0],   j1;
      long long delta = INF;
      for (int j = 1; j <= n; ++j)
        if (!used[j]){
          long long cur = a[i0][j] - u[i0] - v[j];
          if (cur < minv[j])
            minv[j] = cur,  way[j] = j0;
          if (minv[j] < delta)
            delta = minv[j],  j1 = j;
        }
      for (int j = 0; j <= n; ++j)
        if (used[j])
          u[p[j]] += delta,  v[j] -= delta;
        else
          minv[j] -= delta;
      j0 = j1;
    }while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);

    res = max(res, v[0]);
  }

  cout << res << endl;
  return 0;
}