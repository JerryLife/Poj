//
// Created by HUSTW on 2017/12/18.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define maxn 510

int rel[maxn], pre[maxn];

int Init() {
    memset(rel, 0, sizeof(rel));
    for (int i = 0; i < maxn; ++i) {
        pre[i] = i;
    }
}

int Find(int x) {
    int px = pre[x];
    if (px == x)
        return x;
    pre[x] = Find(px);
    rel[x] = (rel[x] + rel[px]) % 3;
    return pre[x];
}

bool Union(int u, int v, int w) {
    int pu = Find(u);
    int pv = Find(v);
    if (pu != pv) {
        pre[pu] = pv;
        rel[pu] = (rel[v] + w - rel[u] + 3) % 3;
        return false;
    }
    else {
        // If collision appears, return 1
        return ((rel[u] - rel[v] + 3) % 3 != w);
    }
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {

        // Each line for u, v, w
        int match[m][3];

        // read input
        for (int i = 0; i < m; ++i) {
            char c;
            scanf("%d%c%d", &match[i][0], &c, &match[i][1]);
            match[i][2] = (c == '>' ? 1 : (c == '=' ? 0 : 2));
        }

        // Guess each i as the judge
        int judge_num = 0, judge, round = 0;
        for (int i = 0; i < n; ++i) {
            Init();

            // Merge each line of input
            bool found = true;
            for (int j = 0; j < m; ++j) {
                int u = match[j][0];
                int v = match[j][1];
                int w = match[j][2];

                // remove every edge connected with possible judge i
                if (u == i || v == i)
                    continue;

                if (Union(u, v, w)) {
                    found = false;
                    round = max(round, j + 1);
                    break;
                }
            }

            if (found) {
                judge = i;    // one more possible judge
                if (++judge_num > 1)
                    break;
            }
        }

        if (judge_num == 0)
            printf("Impossible\n");
        else if (judge_num == 1)
            printf("Player %d can be determined to be the judge after %d lines\n", judge, round);
        else
            printf("Can not determine\n");

        if (!m)
            break;
    }
    return 0;
}