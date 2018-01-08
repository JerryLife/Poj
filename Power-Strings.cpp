//
// Part 3.3: Poj 2406

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

#define nmax 1000100

int next[nmax];
char s[nmax];

int main() {
    while (scanf("%s", s), strcmp(s, ".")) {
        // calculate next
        int i = 0, j = -1;
        next[0] = -1;
        int len = strlen(s);
        while (i < len) {
            if (j == -1 || s[i] == s[j]) {
                ++i, ++j;
                if (s[i] != s[j]) {
                    next[i] = j;
                } else next[i] = next[j];
            } else {
                j = next[j];
            }
        }

        int match = len - next[len];
        if (len % match == 0) {
            printf("%d\n", len / match);
        } else {
            printf("1\n");
        }
    }
    return 0;
}