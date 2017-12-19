#include <iostream>

using namespace std;

int p[50010];
int r[50010];

int find(int x) {
    if (p[x] == x)
        return x;
    else {
        int p_tmp = p[x];
        p[x] = find(p[x]);
        r[x] = (r[x] + r[p_tmp]) % 3;   // Update the relation by mod 3
        return p[x];
    }
}

void merge(int x, int y, int d) {
    int root_x = find(x);
    int root_y = find(y);

    // can be improved by add the small tree to the larger one
    p[root_x] = root_y;
    r[root_x] = (r[y] + d - r[x] + 3) % 3;
}

int main() {

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        r[i] = 0;
    }

    int wrong = 0;

    for (int i = 0; i < k; ++i) {
        int d, x, y;
        scanf("%d%d%d", &d, &x, &y);

        if (x > n || y > n) {
            wrong ++;
            continue;
        }

        if (d == 2 && x == y) {
            wrong ++;
            continue;
        }

        if (find(x) != find(y)) {
            merge(x, y, d-1);
            continue;
        }

        if (d == 1) {       //same  group
            if ((r[x] - r[y] + 3) % 3 != 0) {
                wrong ++;
                continue;
            }
        }
        else {
            // d == 2
            if ((r[x] - r[y] + 5) % 3 != 0) {
                wrong ++;
                continue;
            }
        }
    }

    cout << wrong << endl;
}
