//
// Created by HUSTW on 2017/12/29.
// Part 6.3: Poj 1201

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

#define nmax 51000
#define mmax 210010

struct Edge {
    int v, w, next;
    Edge() {}
    Edge(int v, int w, int next) : v(v), w(w), next(next) {}
} edges[mmax];

int n, m, cnt = 0;
int head[nmax], d[nmax];
int visited[nmax], v_time[nmax];

int addEdge(int u, int v, int w) {
    edges[cnt] = Edge(v, w, head[u]);
    head[u] = cnt++;    // to the first element
}

int init() {
    memset(head, -1, sizeof(head));
    memset(visited, 0, sizeof(visited));
    memset(v_time, 0, sizeof(v_time));
    memset(d, 0x3f, sizeof(d));
}

bool SPFA(int start, int end) {
    d[start] = 0;
    visited[start] = true;
    // pair< distance, node > ranked as distance
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(pair<int, int>(0, start));

    while (!q.empty()) {
        pair<int, int> p;   // top element
        p = q.top();
        q.pop();
        visited[p.second] = false;

        if (v_time[p.second]++ > end)
            return false;   // negative loop

        for (int i = head[p.second]; i != -1; i = edges[i].next) {
            int u = p.second;
            int v = edges[i].v;
            int w = edges[i].w;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(pair<int, int>(d[v], v));
                }
            }
        }
    }

    return true;
}

int main() {
    scanf("%d", &n);
    init();
    int l = INT_MAX, r = INT_MIN;
    for (int i = 0; i < n; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        addEdge(b+1, a, -c);
        l = min(a, l);
        r = max(b, r);
    }

    for (int i = l+1; i <= r+1; ++i) {
        addEdge(i, i-1, 0);
        addEdge(i-1, i, 1);
    }

    if (SPFA(r+1, r-l+2)) {
        printf("%d", -d[l]);
    }
    return 0;
}