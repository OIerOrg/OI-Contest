#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, m, d, k;
int cnt[N];
int leafover[N];
int main() {
    scanf("%d%d%d%d", &n, &m, &k, &d);
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        cnt[x] += y;
        for (int i = 1; i <= n; i++)
            leafover[i] = k;
        bool ok = true;
        for (int i = 1; i <= n; i++) {
            int j = i, Cnt = cnt[i];
            while (Cnt && j <= i + d) {
                int k = min(leafover[j], Cnt);
                Cnt -= k;
                leafover[j] -= k;
                j++;
            }
            if (j > i + d && Cnt > 0) {
                ok = false;
                break;
            }
        }
        if (ok)
            puts("YES");
        else
            puts("NO");
    }
}