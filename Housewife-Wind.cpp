//
// Part 4.3: Poj 2763

#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<set>

using namespace std;

#define nmax 111111
#define Clear(x, y) memset((x), (y), sizeof(x))
int sum[nmax << 2];

struct Edge {
    int v;
    int next;
} edge[nmax << 1];

int head[nmax];
int cnt, q, s, m[nmax][3];

int query(int root, int l, int r, int ql, int qr) {
    int ans = 0;
    int mid = (l + r) >> 1;
    if (ql <= l && qr >= r)
        return sum[root];
    if (ql <= mid)
        ans += query(root << 1, l, mid, ql, qr);
    if (mid < qr)
        ans += query(root << 1 | 1, mid + 1, r, ql, qr);
    return ans;
}

int update(int root, int l, int r, int p, int v) {
    int mid = (l + r) >> 1;
    if (l != r) {
        if (p > mid)
            update(root << 1 | 1, mid + 1, r, p, v);
        else update(root << 1, l, mid, p, v);
        sum[root] = sum[root << 1] + sum[root << 1 | 1];
        return 1;
    }
    sum[root] = v;
    return 0;
}

int n, num;
int size[nmax], child[nmax], depth[nmax], top[nmax], pa[nmax], p[nmax];

void init() {
    Clear(head, -1);
    Clear(sum, 0);
    Clear(child, 0);
    cnt = 0;
    num = 0;
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void dfs(int v, int f) {
    size[v] = 1;
    int flag = 0;
    int i = head[v];
    while (i + 1) {
        int u = edge[i].v;
        if (u != f) {
            depth[u] = depth[v] + 1;
            pa[u] = v;
            dfs(u, v);
            size[v] += size[u];
            if (size[v] > flag) {
                child[v] = u;
                flag = size[u];
            }
        }
        i = edge[i].next;
    }
}

void dfs2(int v, int tp) {
    top[v] = tp;
    p[v] = ++num;
    if (child[v])
        dfs2(child[v], tp);
    int i = head[v];
    while (i + 1) {
        int u = edge[i].v;
        if (u != child[v] && u != pa[v])
            dfs2(u, u);
        i = edge[i].next;
    }
}

int Find(int u, int v) {
    int ans = 0;
    for (int fu = top[u], fv = top[v]; fu - fv; ) {
        if (depth[fu] < depth[fv]) {
            swap(fu, fv);
            swap(u, v);
        }
        ans += query(1, 1, n, p[fu], p[u]);
        u = pa[fu];
        fu = top[u];
    }
    if (u != v) {
        if (depth[u] < depth[v])
            swap(u, v);
        ans += query(1, 1, n, p[v] + 1, p[u]);
    }
    return ans;
}

int main() {
    //freopen("input.txt", "r", stdin);
    while(~scanf("%d%d%d", &n, &q, &s)) {
        init();
        for(int i = 1; i < n; i++) {
            scanf("%d%d%d", &m[i][0], &m[i][1], &m[i][2]);
            int u = m[i][0];
            int v = m[i][1];
            edge[cnt].v = v;
            edge[cnt].next = head[u];
            head[u] = cnt;
            ++cnt;
            edge[cnt].v = u;
            edge[cnt].next = head[v];
            head[v] = cnt;
            ++cnt;
        }
        dfs(1, 0);
        dfs2(1, 1);
        for(int i = 1; i < n; i++) {
            if(depth[m[i][0]] < depth[m[i][1]]) 
                swap(m[i][0], m[i][1]);
            update(1, 1, n, p[m[i][0]], m[i][2]);
        }
        int op, a, b;
        for(int i = 1; i <= q; i++) {
            scanf("%d", &op);
            if(op == 0) {
                scanf("%d", &a);
                printf("%d\n", Find(s, a));
                s = a;
            }
            else {
                scanf("%d%d", &a, &b);
                update(1, 1, n, p[m[a][0]], b);
            }
        }
    }
    return 0;
}