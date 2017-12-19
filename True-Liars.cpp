#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 650;

int rel[maxn], pre[maxn];

int Find(int x) {
    int px = pre[x];
    if (px == x)
        return x;
    pre[x] = Find(px);
    rel[x] = rel[x] ^ rel[px];
    return pre[x];
}

void Union(int a, int b, int w) {
    int pa = Find(a);
    int pb = Find(b);
    if (pa != pb) {
        pre[pa] = pb;
        rel[pa] = rel[a] ^ rel[b] ^ w;
    }
}

void Init() {
    for (int i = 0; i < maxn; ++i) {
        pre[i] = i;
    }
    memset(rel, 0, maxn);

}

int main() {

    int n, p1, p2;

    while (true) {
        scanf("%d%d%d", &n, &p1, &p2);
        if (!n && !p1 && !p2)
            break;

        Init();
        // Union all the data
        while (n--) {
            int u, v, w;
            char s[5];
            scanf("%d%d%s", &u, &v, s);
            w = (s[0] == 'n');
            Union(u, v, w);
        }

        // ensure every node's parent is root
        for (int i = 0; i < p1 + p2; ++i) {
            Find(i);
        }


    }
}