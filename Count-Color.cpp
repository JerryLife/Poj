//
// Part 5.1: Poj 2777

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

#define nmax 100010

using namespace std;

struct STNode {
    int l;
    int r;
    int val;        // 32 bits correspond to 32 (maybe less) colors
    bool cover;     // if the interval is covered by only one color
} tree[3 * nmax];

int n, T;

void build(int l, int r, int root) {
    tree[root].val = 1;
    tree[root].l = l;
    tree[root].r = r;
    tree[root].cover = true;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(l, mid, 2*root);
    build(mid+1, r, 2*root+1);
    tree[root].val = 1;     // all initial values are 1
}

void push_down(int root) {
    if (tree[root].cover) {
        tree[root].cover = false;
        tree[2 * root].val = tree[2 * root + 1].val = tree[root].val;
        tree[2 * root].cover = tree[2 * root + 1].cover = true;
    }
}

void update(int l, int r, int root, int val) {
    if (r < tree[root].l || l > tree[root].r)
        return;
    if (l <= tree[root].l && r >= tree[root].r) {
        tree[root].val = val;
        tree[root].cover = true;
        return;
    }

    push_down(root);
    if (r >= tree[2*root].l)
        update(l, r, 2*root, val);
    if (l <= tree[2*root+1].r)
        update(l, r, 2*root+1, val);
    tree[root].val = tree[2*root].val | tree[2*root+1].val;
}


int count_sum(int n) {
    // count the number of 1 in sum
    int cnt = 0;
    while (n) {
        n &= n-1;
        ++cnt;
    }
    return cnt;
}

int sum = 0;
int query(int l, int r, int root) {
    if (tree[root].cover ||
            (tree[root].l >= l && tree[root].r <= r)) {
        sum |= tree[root].val;      // add this color to sum
        return sum;
    }
    if (l <= tree[2*root].r)
        sum |= query(l, r, 2*root);
    if (r >= tree[2*root+1].l)
        sum |= query(l, r, 2*root+1);
    return sum;
}

int main() {
    int line;
    scanf("%d%d%d", &n, &T, &line);
    build(1, n, 1); // root is 1
    while (line--) {
        getchar();
        int op = getchar();
        if (op == 'C'){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            if (b < a)  // ensure a <= b
                swap(a, b);
            // add color
            update(a, b, 1, 1 << (c-1));
        }
        else {
            int a, b;
            scanf("%d%d", &a, &b);
            if (b < a)  // ensure a <= b
                swap(a, b);
            // print colors
            sum = 0;
            int ans = count_sum(query(a, b, 1));
            printf("%d\n", ans);
        }
    }
    return 0;
}

