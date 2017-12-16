#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 11111

using namespace std;
struct Claim {
    int u;
    int v;
    int w;
};


int r[maxn], p[maxn], f[maxn];
Claim cs[maxn];

// UnionFind from right to left
// r indicates relation (0 for even, 1 for odd)
int Find(int x) {
    if (x == p[x])
        return x;
    r[x] = (r[x] + r[p[x]]) % 2;
    p[x] = Find(p[x]);
    return p[x];
}

int Union(int a, int b, int w) {
    int pa = Find(a);
    int pb = Find(b);
    if (pa == pb) {
        return (r[a] ^ r[b] == w);
    }
    else {
        // pa > pb
        r[pa] = r[a] ^ r[b] ^ w;
        p[pa] = pb;
        return 1;
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    // read all data, and create a hash map
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        Claim c;
        char s[10];
        scanf("%d%d%s", &c.u, &c.v, s);
        c.u --;         // this line is really important
        c.w = strcmp(s, "even");  // even = 0, odd = 1
        cs[i] = c;
        f[cnt++] = c.u;
        f[cnt++] = c.v;
    }

    sort(f, f + cnt);       // sort the hash table
    cnt = (int)(unique(f, f + cnt) - f);    // remove duplicate

    // initialize
    for (int i = 0; i < cnt; ++i) {
        p[i] = i;
        r[i] = 0;
    }

    int i;
    for (i = 0; i < m; ++i) {
        // find elements in hash table
        int a = (int)(lower_bound(f, f + cnt, cs[i].u) - f);
        int b = (int)(lower_bound(f, f + cnt, cs[i].v) - f);

        // check if collision
        if (Union(a, b, cs[i].w) == 0)
            break;
    }
    printf("%d\n", i);
    return 0;
}