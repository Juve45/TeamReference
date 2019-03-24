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

using namespace std;

#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
#define forab(i,a,b) for (int i = int(a); i < int(b); ++i)

typedef long long ll;
typedef long double ld;

const int INF = 1000001000;
const ll INFL = 2000000000000001000;

const int maxn = 500;

ll g[maxn][maxn];
ll dist[maxn];
bool used[maxn];

void addEdge(int u, int v, ll c)
{
    g[u][v] += c;
    g[v][u] += c;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    ll total = 0;
    forn (i, m)
    {
        int k, f;
        scanf("%d%d", &k, &f);
        total += 2 * f;
        vector<int> group;
        forn (j, k)
        {
            int u;
            scanf("%d", &u);
            --u;
            group.push_back(u);
        }
        if (k == 2)
            addEdge(group[0], group[1], 2 * f);
        else
        {
            addEdge(group[0], group[1], f);
            addEdge(group[1], group[2], f);
            addEdge(group[2], group[0], f);
        }
    }
    vector<int> vertices;
    forn (i, n)
        vertices.push_back(i);
    ll mincut = total + 1;
    while (sz(vertices) > 1)
    {
        int u = vertices[0];
        for (auto v: vertices)
            used[v] = false,
            dist[v] = g[u][v];
        used[u] = true;
        forn (ii, sz(vertices) - 2)
        {
            for (auto v: vertices)
                if (!used[v])
                    if (used[u] || dist[v] > dist[u])
                        u = v;
            used[u] = true;
            for (auto v: vertices)
                if (!used[v])
                    dist[v] += g[u][v];
        }
        int t = -1;
        for (auto v: vertices)
            if (!used[v])
                t = v;
        mincut = min(mincut, dist[t]);
        vertices.erase(find(vertices.begin(), vertices.end(), t));
        for (auto v: vertices)
            addEdge(u, v, g[v][t]);
    }

    cout << (total - mincut) / 2 << '\n';
    return 0;
}