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

int n, m, cnt = 0, clerk_n;
int r[25], t[25];
int head[nmax], d[nmax];
int visited[nmax], v_time[nmax];

int addEdge(int u, int v, int w) {
    edges[cnt] = Edge(v, w, head[u]);
    head[u] = cnt++;    // to the first element
}

int init() {
    memset(r, 0, sizeof(r));
    memset(t, 0, sizeof(t));
}

int clear() {
    memset(visited, 0, sizeof(visited));
    memset(v_time, 0, sizeof(v_time));
    memset(d, -1, sizeof(d));
}

int build(int sum) {
    cnt = 0;
    memset(head, -1, sizeof(head));
    addEdge(0, 24, sum);
    for (int i = 1; i <= 24; ++i) {
        addEdge(i - 1, i, 0);
        addEdge(i, i - 1, -t[i]);
    }
    for (int i = 1; i <= 24; ++i) {
        if (i <= 8)
            addEdge(i + 16, i, r[i] - sum);
        else
            addEdge(i - 8, i, r[i]);
    }
}

bool SPFA(int sum) {
    clear();
    // start at 0
    int start = 0;
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

        if (v_time[p.second]++ > 24)
            return false;   // negative loop

        for (int i = head[p.second]; i != -1; i = edges[i].next) {
            int u = p.second;
            int v = edges[i].v;
            int w = edges[i].w;
            if (d[u] + w > d[v]) {
                d[v] = d[u] + w;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(pair<int, int>(d[v], v));
                }
            }
        }
    }

    return (d[24] == sum);
}

int scan() {
    for (int i = 0; i <= clerk_n; ++i) {
        build(i);
        if (SPFA(i)) {
            return i;
        }
    }
    return -1;
}

int main() {

    scanf("%d", &n);
    while (n--) {
        init();
        // deal with input
        for (int i = 1; i <= 24; ++i) {
            scanf("%d", r + i);
        }
        scanf("%d", &clerk_n);
        for (int i = 1; i <= clerk_n; ++i) {
            int tmp;
            scanf("%d", &tmp);
            ++t[tmp + 1];
        }

        int rst;
        if ((rst = scan()) != -1)
            printf("%d\n", rst);
        else
            printf("No Solution\n");
    }
    return 0;
}