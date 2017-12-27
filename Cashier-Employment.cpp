//
// Part 6.2: Poj 1275

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

#define nmax 30010
#define mmax 150010

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

bool SPFA() {
    // start at 1
    d[1] = 0;
    // pair< distance, node > ranked as distance
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(pair<int, int>(0, 1));

    while (!q.empty()) {
        pair<int, int> p;   // top element
        p = q.top();
        q.pop();
        visited[p.second] = false;

        if (v_time[p.second]++ > n)
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
    scanf("%d %d", &n, &m);
    init();
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }
    if (SPFA())
        printf("%d", d[n]);
    return 0;
}