#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define nmax 20010

long long BIT[2][nmax];  // row 0 for number of points lower than x, row 1 for sum of points indices before.
int n;
vector<pair<long long, long long> > cows;    // cow.first = volume, cow.second = x

int lowbit(int x) {
    return x & (-x);
}

void add(int x, long long v, int type) {
    for (int i = x; i <= nmax; i += lowbit(i)) {
        BIT[type][i] += v;
    }
}

long long sum(int x, int type) {
    long long s = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        s += BIT[type][i];
    }
    return s;
}

int main() {
    scanf("%d", &n);

    // store all inputs
    for (int i = 0; i < n; ++i) {
        pair<long long, long long> cow;
        scanf("%lld%lld", &cow.first, &cow.second);
        cows.push_back(cow);
    }

    // sort by cow.volume (cow.first)
    sort(cows.begin(), cows.end());

    long long v_sum = 0, i = 0;
    while(i < n - 1) {
        // build two BITs
        long long x = cows[i].second;
        add(x, 1, 0);
        add(x, x, 1);

        // calculate sum
        x = cows[++i].second;
        long long v = cows[i].first;
        long long a = sum(x, 0);
        long long b = sum(x, 1);
        long long all = sum(nmax - 1, 1);

        long long l = a * x - b;
        long long r = all - b - (i - a) * x;
        v_sum += (l + r) * v;
    }

    printf("%lld", v_sum);
}