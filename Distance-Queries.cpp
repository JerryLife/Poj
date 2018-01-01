//
// Part 4.2: Poj 1986

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

#define nmax 111111
#define Clear(x, y) memset((x), (y), sizeof(x))

int head[nmax], pa[nmax], qhead[nmax], visit[nmax], d[nmax];
int n, m, round, cnt;

struct EdgeNode
{
    int u;
    int v;
    int w;
    int l;
    int next;
}e[nmax], q[nmax];

int Find(int x)
{
    if (x == pa[x])
        return x;
    return pa[x] = Find(pa[x]);
}

void Union(int a,int b)
{
    int ap = Find(a);
    int bp = Find(b);
    if(ap != bp)
        pa[bp] = ap;
}

void addEdge(int u,int v,int w) {
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt++;
}

void addq(int u,int v) {
    q[cnt].u = u;
    q[cnt].v = v;
    q[cnt].l = -1;
    q[cnt].next = qhead[u];
    qhead[u] = cnt++;
}

void tarjan(int u) {
    pa[u] = u;
    visit[u] = 1;
    int k = head[u];
    while (k + 1) {
        int v = e[k].v;
        if (visit[v]) {
            k = e[k].next;
            continue;
        }
        d[v] = d[u] + e[k].w;
        tarjan(v);
        Union(u, v);
        k = e[k].next;
    }
    k = qhead[u];
    while (k + 1) {
        int v = q[k].v;
        if (!visit[v]) {
            k = q[k].next;
            continue;
        }
        q[k].l = Find(v);
        q[k ^ 1].l = q[k].l;
        k = q[k].next;
    }
}

void init() {
    cnt = 0;
    for (int i = 1; i <= n; i++)
        pa[i] = i;
    Clear(d, 0);
    Clear(visit, 0);
    Clear(head, -1);
    Clear(qhead, -1);
}

int main() {
    scanf("%d%d", &n, &m);
    init();
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        char buf[66];
        scanf("%d%d%d%s", &x, &y, &w, buf);
        addEdge(x, y, w);
        addEdge(y, x, w);
    }
    scanf("%d", &round);
    cnt = 0;
    
    for (int i = 0; i < round; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        addq(x, y);
        addq(y, x);
    }
    tarjan(1);
    for (int i = 0; i < round; i++) {
        int u, v, l;
        u = q[i << 1].u;
        v = q[i << 1].v;
        l = q[i << 1].l;
        printf("%d\n", d[u] + d[v] - (d[l] << 1));
    }
}
