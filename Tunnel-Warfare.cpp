#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

#define nmax 50010

int BIT[nmax];
int n, m;
stack<int> des;

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
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

int bin_find(int s, int t, int type) {
    int m;
    int rst;
    if (type == 0) {
        while (t >= s) {
            m = (s + t) / 2;
            if (sum(t) - sum(m - 1) == t - m + 1) {
                rst = m;
                t = m - 1;
            } else {
                s = m + 1;
            }
        }
    } else {
        while (t >= s) {
            m = (s + t) / 2;
            if (sum(m) - sum(s - 1) == m - s + 1) {
                rst = m;
                s = m + 1;
            } else {
                t = m - 1;
            }
        }
    }
    return rst;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        add(i, 1);
    }

    while (m--) {
        char op[5];
        int v;
        scanf("%s", op);
        if (op[0] == 'D') {
            scanf("%d", &v);
            des.push(v);
            add(v, -1);
        }
        else if (op[0] == 'R') {
            int last = des.top();
            des.pop();
            add(last, 1);
        }
        else {
            // op == 'Q'
            scanf("%d", &v);
            if (sum(v) - sum(v-1) == 0)
                printf("0\n");
            else {
                // binary search
                int l = bin_find(1, v, 0);
                int r = bin_find(v, n, 1);
                printf("%d\n", r - l + 1);
            }
        }
    }
    return 0;
}