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

int i, n, q, a[N], x, y, z;

struct node;
typedef node* ln;
 
struct node
{
    int pr;
 
    int v;
    int dp;
 
    int id,sz;
     
    ln l, r;
 
    node (int v=0) : pr(rand() * rand() * rand()),v(v),l(0),r(0) { upd(); }
 
    void upd()
    {
        dp = v;
        if (l) dp=max(dp,l->dp);     
        if (r) dp=max(dp,r->dp);
             
        sz = 1;
        if (l) sz+=l->sz;
        id = sz;        
        if (r) sz+=r->sz;        
    }
};
 
ln root;
 
void split ( ln t, int x, ln &l, ln &r)
{
    l=r=0;
    if (!t) return;
    if (t->id <= x)
    {
        split(t->r, x - t->id, t->r, r);
        l = t;
    } else
    {
        split(t->l, x, l, t->l);
        r = t;
    }
 
    t->upd();
}
 
ln merge(ln l, ln r)
{
    if (!l || !r) return (l?l:r);
 
    if (l->pr > r->pr)
    {
        l->r = merge(l->r, r);
        l->upd();
        return l;
    } else
    {
        r->l = merge(l,r->l);
        r->upd();
        return r;
    }
}
 
void insert(int x, int p)
{
    ln l,r;
    split(root,p,l,r);
    root = merge(merge(l,new node(x)),r);
}
 
void erase(int p)
{
    ln l,r,t;
    split(root,p,l,r);
    split(r,1,r,t);
    root = merge(l,t);
}
 
int query(int x, int y)
{
    ln l,t,r;
    split(root, x, l, t);
    split(t, y-x+1, t, r);
     
    int m = t->dp;
     
    root = merge(merge(l,t),r);
    return m;
}

void show(ln t)
{
    if (!t) return;
    show(t->l);
    cout<<' '<<t->v;
    show(t->r);
}

int getPoz(int p)
{
    ln l,r,t;
    split(root,p,l,r);
    split(r,1,r,t);
    int ans = r->v;
    r = merge(r,t);
    root = merge(l, r);
    return ans;
}

int main() {
  srand(time(0));
  root = 0;
  scanf("%d %d", &n, &q);
  for(i = 0; i < n; ++i) scanf("%d", a + i), insert(a[i], i);
  while(q--) {
    scanf("%d %d %d", &x, &y, &z);
    if(x == 1) {
      printf("%d\n", query(y - 1, z - 1));
      continue;
    }

    --z; x = getPoz(z);
    erase(z);
    if(y == 1) {
      insert(x, n - 1);
    } else {
      insert(x, 0);
    }
  }
  return 0;
}