#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <set>
#include <vector>

#define maxn 11111

using namespace std;

int r[maxn], p[maxn], f[maxn];

int Find(int x) {
    if (x == p[x])
        return x;
    r[x] = (r[x] + r[p[x]]) % 2;
    p[x] = Find(p[x]);
    return p[x];
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    while (m-- > 0) {

    }
}