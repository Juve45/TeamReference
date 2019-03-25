/**
 * Author: Cristian Vintur
 * Date: 2019-03-24
 * License: CC0
 * Description: Returns the maximum matching of a bipartite graph
 */

int l[NMAX], r[NMAX];
bool vis[NMAX], ok[NMAX], coverL[NMAX], coverR[NMAX];
vector<int> adj[NMAX], adjt[NMAX];
bool pairUp(int v) {
	if(vis[v]) return false;
	vis[v] = true;
	for(auto u : adj[v])
		if(!r[u]) {
			l[v] = u;
			r[u] = v;
			return true;
		}
	for(auto u : adj[v])
		if(pairUp(r[u])) {
			l[v] = u;
			r[u] = v;
			return true;
		}
	return false;
}
int matching(int n) {
	int sz;
	bool changed;
	for(sz = 0, changed = true; changed; ) {
		memset(vis, 0, sizeof vis);
		changed = false;
		for(int i = 1; i <= n; ++i)
			if(!l[i] && pairUp(i)) ++sz, changed = true;
	}
	return sz;
}
void bfs(vector<int> adj[], int l[], int r[], int n) {
	queue<int> q;
	memset(vis, 0, sizeof vis);
	for(int i = 1; i <= n; ++i) if(!l[i]) q.push(i), vis[i] = true;
	for(; !q.empty(); q.pop()) {
		int v = q.front();
		ok[v] = true;
		for(auto u : adj[v])
			if(!vis[r[u]]) q.push(r[u]), vis[r[u]] = true;
	}
}
void cover(int v) {
	for(auto u : adj[v])
		if(!coverR[u]) {
			coverR[u] = true;
			coverL[r[u]] = false;
			cover(r[u]);
		}
}
sz = matching(n);
// getting all vertices which do NOT belong to ALL maximum matchings
// if ok[i] == false => i belongs to all maximum matchings
bfs(adj, l, r, n);
bfs(adjt, r, l, n);
//getting minimum vertex cover
for(int i = 1; i <= n; ++i) if(l[i]) coverL[i] = true;
for(int i = 1; i <= n; ++i) if(!l[i]) cover(i);
