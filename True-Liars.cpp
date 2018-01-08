#include <cstdio>
#include<cstring>
#include<map>

#define nmax 650

using namespace std;

typedef map<int, int> Map;

int bag[nmax][2];
Map bagmap;
int cnt;
int dp[nmax][310];
int pa[nmax];
int re[nmax];
int choose[nmax];

int insert(int x,int b) {
    if (bagmap.find(x) == bagmap.end())
        bagmap[x] = ++cnt;
    ++bag[bagmap[x]][b];//该分量的b类人加1
    return bagmap[x];
}

int Find(int i) {
    if (pa[i] == -1)
        return i;
    int tmp = Find(pa[i]);
    re[i] = (re[i] + re[pa[i]]) & 1;
    return pa[i] = tmp;
}

void Union(int u,int v,int w) {
    int fa = Find(u);
    int fb = Find(v);
    if (fa != fb) {
        pa[fb] = fa;
        re[fb] = (re[u] + re[v] + w) & 1;
    }
}

void Init() {
    cnt = 0;
    bagmap.clear();
    memset(bag, 0, sizeof(bag));
    memset(pa, -1, sizeof(pa));
    memset(re, 0, sizeof(re));
    memset(dp, 0, sizeof(dp));
    memset(choose, -1, sizeof(choose));
}

int main() {
    int n, p1, p2;
    while (scanf("%d%d%d", &n, &p1, &p2)) {
        if (!(n || p1 || p2))
            return 0;
        Init();
        for (int l = 0; l < n; ++l) {
            int a, b, type = 0;
            char str[15];
            scanf("%d%d%s", &a, &b, str);
            switch (str[0]) {
                case 'y': type = 0;
                    break;
                case 'n': type = 1;
                    break;
                default:
                    break;
            }
            if (Find(a) != Find(b))
                Union(a, b, type);
        }
        int i = 0;
        while (++i <= p1 + p2)
        {
            int fi = Find(i);
            insert(fi, re[i]);
        }

        // dp
        dp[0][0] = 1, i = 0;
        while (++i <= cnt)
        {
            for (int j = 0; j <= p1; j++) {
                for (int k = 0; k < 2; ++k) {
                    if (j >= bag[i][k])
                        dp[i][j] = k * dp[i][j] + dp[i - 1][j - bag[i][k]];
                }
            }
        }

        if (dp[cnt][p1] == 1)
        {
            int j = p1;
            for (int k = cnt; k >= 1; k--)
            {
                for (int l = 0; l < 2; ++l) {
                    if (dp[k][j] == dp[k - 1][j - bag[k][l]]) {
                        choose[k] = l;
                        j -= bag[k][l];
                        break;
                    }
                }
            }
            i = 0;
            while (++i <= p1 + p2) {
                int num = bagmap[Find(i)];
                if (re[i] == choose[num])
                    printf("%d\n", i);
            }
            printf("end\n");
        } else {
            printf("no\n");
        }

    }
    return 0;
}