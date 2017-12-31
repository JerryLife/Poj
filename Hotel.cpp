//
// Part 5.4: Poj 3667

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

#define nmax 66666

using namespace std;

struct STNode {
    int l;
    int r;
    int ls;
    int ms;
    int rs;
    int state;
} tree[3 * nmax];

int n, m;

inline int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

void build(int l, int r, int root) {
    tree[root].l = l;
    tree[root].r = r;
    // all valid
    tree[root].ls = tree[root].ms = tree[root].rs = r-l+1;
    if (l == r) {
        tree[root].state = -1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2*root);
    build(mid+1, r, 2*root+1);
}

void push_down(int root) {
    if (tree[root].state == -1)
        return;

    tree[2*root].state = tree[2*root+1].state = tree[root].state;
    if (tree[root].state == 1) {
        // move in
        tree[2*root].ls = tree[2*root].rs = tree[2*root].ms = 0;
        tree[2*root+1].ls = tree[2*root+1].rs = tree[2*root+1].ms = 0;
    }
    else if (tree[root].state == 0) {
        // check out
        int ltotal = tree[2*root].r - tree[2*root].l + 1;
        int rtotal = tree[2*root+1].r - tree[2*root+1].l + 1;
        tree[2*root].ls = tree[2*root].rs = tree[2*root].ms = ltotal;
        tree[2*root+1].ls = tree[2*root+1].rs = tree[2*root+1].ms = rtotal;
    }
    tree[root].state = -1;
}

void update(int l, int r, int root, int state) {
    if (r < tree[root].l || l > tree[root].r)
        return;
    if (l <= tree[root].l && r >= tree[root].r) {
        if (state == 1) {
            // all check in
            tree[root].ls = tree[root].rs = tree[root].ms = 0;
            tree[root].state = 1;
        }
        else if (state == 0) {
            // all check out
            int total = tree[root].r - tree[root].l + 1;
            tree[root].ls = tree[root].rs = tree[root].ms = total;
            tree[root].state = 0;
        }
        return;
    }

    push_down(root);
    if (r >= tree[2*root].l)
        update(l, r, 2*root, state);
    if (l <= tree[2*root+1].r)
        update(l, r, 2*root+1, state);

    // update ls
    if (tree[2*root].ls == tree[2*root].r - tree[2*root].l + 1) {
        tree[root].ls = tree[2*root].ls + tree[2*root+1].ls;
    } else {
        tree[root].ls = tree[2*root].ls;
    }

    // update rs
    if (tree[2*root+1].rs == tree[2*root+1].r - tree[2*root+1].l + 1) {
        tree[root].rs = tree[2*root+1].rs + tree[2*root].rs;
    } else {
        tree[root].rs = tree[2*root+1].rs;
    }

    // update ms
    tree[root].ms = max3(tree[2*root].ms, tree[2*root+1].ms, tree[2*root].rs + tree[2*root+1].ls);
}

int st;
int query(int l, int r, int root, int size) {
    if (tree[root].ms < size)
        return st;
    if (tree[root].ls >= size)
        return st = tree[root].l;
    if (tree[2*root].ms >= size) {
        push_down(root);
        return st = query(l, tree[2*root].r, 2*root, size);
    }
    if (tree[2*root].rs + tree[2*root+1].ls >= size) {
        return st = tree[2*root].r - tree[2*root].rs + 1;
    }
    if (tree[2*root+1].ms >= size) {
        push_down(root);
        return st = query(tree[2*root+1].l, r, 2*root+1, size);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    build(1,n, 1);
    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int size;
            st = 0;     // clear st every time!!!!!
            scanf("%d", &size);
            int st = query(1, n, 1, size);
            printf("%d\n", st);
            if(st)
                update(st, st + size - 1, 1, 1);
        }
        else {
            // op == 2
            int x, size;
            scanf("%d%d", &x, &size);
            update(x, x+size-1, 1, 0);
        }
    }
    return 0;
}
