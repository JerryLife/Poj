// Use C++ instead of G++, or you will get TLE
// Part 2.4: Poj 2481

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

#define nmax 100010

int BIT[nmax];
int ans[nmax];
int n;

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int v) {
    for (int i = x; i <= nmax; i += lowbit(i)) {
        BIT[i] += v;
    }
}

int sum(int x) {
    int s = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        s += BIT[i];
    }
    return s;
}

struct Cow {
    int l;
    int r;
    int i;
} cows[nmax];

bool cmp(Cow a, Cow b) {
    if (a.r == b.r) {
        return a.l < b.l;
    }
    else return a.r > b.r;
}

int main() {
    while (scanf("%d", &n), n) {
        memset(BIT, 0, sizeof(BIT));
        memset(ans, 0, sizeof(ans));

        // store every input
        for (int i = 0; i < n; ++i) {
            scanf(" %d %d", &cows[i].l, &cows[i].r);
            ++cows[i].l;
            cows[i].i = i;
        }

        // sort by right range
        sort(cows, cows + nmax, cmp);

        // calculate sum
        for (int i = 0; i < n; add(cows[i++].l, 1)) {
            if (i != 0 && cows[i].l == cows[i-1].l && cows[i].r == cows[i-1].r) {
                // totally equal
                ans[cows[i].i] = ans[cows[i-1].i];
            } else {
                ans[cows[i].i] = sum(cows[i].l);
            }
        }

        for (int i = 0; i < n-1; ++i) {
            printf("%d ", ans[i]);
        }
        printf("%d\n", ans[n-1]);
    }
    return 0;
}