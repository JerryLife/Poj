//
// Part 2.1: Poj 3321

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define nmax 100010

int start[nmax], end[nmax];
int n, m;
int tree[nmax];
bool is_apple[nmax];
vector<vector<int> > ad_list(nmax);

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tree[i] += v;
    }
}

int sum(int x) {
    int s = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        s += tree[i];
    }
    return s;
}

void dfs(int s) {
    static int round = 1;
    start[s] = round;
    for (int i = 0; i < ad_list[s].size(); ++i) {
        ++round;
        dfs(ad_list[s][i]);
    }
    end[s] = round;
}

int main() {
    scanf("%d", &n);

    // build the whole tree
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        ad_list[u].push_back(v);    // Only one way edge is needed
    }

    // run dfs, store dfs numbers in ad_list
    dfs(1);

    for (int i = 1; i <= n; ++i) {
        add(start[i], 1);
        is_apple[i] = true;
    }

    scanf("%d", &m);

    for (int i = 0; i < m; ++i) {
        char op;
        int x;
        scanf(" %c %d", &op, &x);   // use space to remove \n
        if (op == 'Q') {
            int rst = sum(end[x]) - sum(start[x] - 1);
            printf("%d\n", rst);
        } else {
            // if op == 'C'
            if (is_apple[x])
                add(start[x], -1);
            else add(start[x], 1);
            is_apple[x] = !is_apple[x];
        }
    }

    return 0;
}