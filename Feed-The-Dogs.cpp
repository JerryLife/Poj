//
// Part 5.3: Poj 2761

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

#define nmax 100100
#define mmax 55555

using namespace std;

struct ChairTree{
    int l;
    int r;
    int s;
} tree[3*nmax];

struct Node{
    int a;
    int b;
    int k;
    int idx;
}p[mmax];

int res[mmax];
int n, m;
int s[nmax], t[nmax];
int find_rst, mark;

inline bool cmp(Node x,Node y){
    return x.a < y.a;
}

void build(int l, int r, int root){
    tree[root].l = l;
    tree[root].r = r;
    tree[root].s = 0;
    if(l == r)
        return;
    int mid = (l + r) / 2;
    build(l, mid, 2*root);
    build(mid+1, r, 2*root+1);
}

void update(int r,int x,int flag){
    if(tree[r].l != tree[r].r) {
        int mid = (tree[r].l + tree[r].r) / 2;
        if (x > mid) {
            update(2 * r + 1, x, flag);
        } else {
            tree[r].s += flag;
            update(2 * r, x, flag);
        }
    }
}

int solve(int r,int v){
    int rst = 0;
    if(tree[r].l == tree[r].r)
        rst = tree[r].l;
    else if(v <= tree[r].s)
        rst = solve(2*r, v);
    else rst = solve(2*r+1, v-tree[r].s);
    return rst;
}

void find(int l, int r){
    int mid = 0;
    while(l <= r){
        mid = (l + r) / 2;
        if (t[mid] < mark) {
            l = mid + 1;
        }
        else if (t[mid] > mark){
            r = mid - 1;
        }
        else {
            find_rst = mid;
            return;
        }
    }
    find_rst = -2;
}

int main(){
    scanf("%d%d", &n, &m);
    int i = 0;
    while (++i <= n){
        scanf("%d", t + i);
    }
    memcpy(s + 1, t + 1, n * sizeof(int));
    sort(t + 1, t + n + 1);
    int num = (int)(unique(t+1, t+n+1) - t-1);
    i = 0;
    while (++i <= n){
        mark = s[i];
        find(1, num);
        s[i] = find_rst;
    }
    build(1, num, 1);
    i = -1;
    while (++i < m){
        scanf("%d%d%d",&p[i].a, &p[i].b, &p[i].k);
        p[i].idx = i;
    }
    sort(p, p+m, cmp);
    int start = p[0].a, end = start;
    i = -1;
    while (++i < m){
        while(start < end && p[i].a > start) {
            update(1, s[start], -1);
            ++start;
        }
        if(end < p[i].a)
            end = p[i].a;
        while(p[i].b >= end) {
            update(1, s[end], 1);
            ++end;
        }
        int rst = solve(1,p[i].k);
        res[p[i].idx] = t[rst];
    }
    i = -1;
    while (++i < m)
        printf("%d\n", res[i]);
    return 0;
}  