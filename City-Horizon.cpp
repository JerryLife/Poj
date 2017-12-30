// nmax = 50000 RE, 80000 AC
// Part 5.2: Poj 3277

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

#define nmax 80000  // 50000 Runtime Error.....

using namespace std;

typedef long long ll;

struct Building {
    ll a;
    ll b;
    ll h;
} buildings[nmax];

struct STNode {
    ll l;
    ll r;
    ll h;       // h = -1 when its height is decided by its children
} tree[3 * nmax];

int n;
ll f[2 * nmax];

inline bool cmp(Building a, Building b) {
    return a.h < b.h;
}

void build(ll l, ll r, ll root) {
    tree[root].l = f[l];
    tree[root].r = f[r];
    if (l + 1 == r)
        return;
    ll mid = (l + r) / 2;
    build(l, mid, 2*root);
    build(mid, r, 2*root+1);
}

void push_down(ll root) {
    if (tree[root].h > 0) {
        tree[2 * root].h = tree[2 * root + 1].h = tree[root].h;
    }
}

void update(ll l, ll r, ll root, ll h) {
    if (l <= tree[root].l && r >= tree[root].r) {
        tree[root].h = h;   // After sorting, this building must be the tallest one
        return;
    }
    push_down(root);
    tree[root].h = -1;
    if (l < tree[2*root+1].l)
        update(l, r, 2*root, h);
    if (r > tree[2*root+1].l)
        update(l, r, 2*root+1, h);
}

ll query(ll root) {
    if (tree[root].h >= 0)
        return tree[root].h * (tree[root].r - tree[root].l);
    else return query(2*root) + query(2*root+1);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld%lld", &buildings[i].a, &buildings[i].b, &buildings[i].h);
        f[2*i-1] = buildings[i].a;
        f[2*i] = buildings[i].b;
    }

    // sort by height
    sort(buildings + 1, buildings + n + 1, cmp);
    sort(f + 1, f + 2*n + 1);
    int len = (int)(unique(f+1, f+2*n+1) - f-1);  // remove duplicate

    build(1, len, 1);
    for (int i = 1; i <= n; ++i) {
        update(buildings[i].a, buildings[i].b, 1, buildings[i].h);
    }
    ll ans = query(1);
    printf("%lld\n", ans);
}
