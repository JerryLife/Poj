//
// Part 6.4: Poj 3165

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

#define nmax 1100
#define mmax 50000

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
    int ml, md;
    scanf("%d%d%d", &n, &ml, &md);
    init();
    while (ml--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
    }
    while (md--) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(v, u, -w);
    }
    for (int i = 1; i < n; ++i) {
        addEdge(i+1, i, 0);
    }

    if (SPFA(1, n)) {
        if (d[n] == 0x3f3f3f3f) {
            printf("-2");
        } else {
            printf("%d", d[n]);
        }
    }
    else printf("-1");

    return 0;
}

