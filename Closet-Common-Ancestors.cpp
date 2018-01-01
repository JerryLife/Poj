//
// Part 4.1: Poj 1470

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

#define nmax 1000
#define Clear(x) memset((x), 0, sizeof(x))

int pa[nmax];   // parents
int visit[nmax];    // if visited
int q[nmax][nmax], child[nmax][nmax];
int sum[nmax];
int root[nmax];

int n;

int find(int x) {
    // like Union-Find
    if (x == pa[x])
        return x;
    pa[x] = find(pa[x]);
    return pa[x];
}

void tarjan(int r) {
    visit[r] = 1;
    for (int i = 1; i <= q[r][0]; ++i) {
        int u = q[r][i];
        if (visit[u] == 1) {
            int p = find(u);
            ++sum[p];
        }
    }

    for (int i = 1; i <= child[r][0]; ++i) {
        int u = child[r][i];
        if (visit[u] == 0) {
            tarjan(u);
            pa[u] = r;
        }
    }
}

void init() {
    Clear(visit);
    Clear(sum);
    Clear(root);
    for (int i = 1; i <= n; ++i) {
        pa[i] = i;
        q[i][0] = 0;
    }
}

int main() {
    while(~scanf("%d", &n)) {
        init();
        int _n = n;
        while (_n--) {
            int j;
            scanf("%d", &j);
            while (true) {
                int c = getchar();
                if (c == '(') {
                    scanf("%d", &child[j][0]);  // nbr of children
                    break;
                }
            }
            while (true) {
                int c = getchar();
                if (c == ')') {
                    for (int k = 1; k <= child[j][0]; ++k) {
                        scanf("%d", &child[j][k]);
                        root[child[j][k]] = 1;
                    }
                    break;
                }
            }
        }

        int m;
        scanf("%d", &m);
        while (m--) {
            int i, j;
            while (true) {
                int c = getchar();
                if (c == '(') {
                    scanf("%d%d", &i, &j);
                    break;
                }
            }
            while (true) {
                int c = getchar();
                if (c == ')') {
                    break;
                }
            }

            // add both edge
            ++q[i][0];
            q[i][q[i][0]] = j;
            ++q[j][0];
            q[j][q[j][0]] = i;
        }

        for (int i = 1; i <= n; ++i)
            if (root[i] == 0) {
                tarjan(i);
                break;
            }
        for (int i = 1; i <= n; ++i)
            if (sum[i] != 0)
                printf("%d:%d\n", i, sum[i]);
    }
    return 0;
}