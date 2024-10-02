#include <bits/stdc++.h>
using namespace std;

int T, n, K;
long long ans, a[100005], sum[100005], f[105][105];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &K);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            sum[i] = sum[i - 1] + a[i];
        }
        if (n <= 100) {
            ans = 1e15;
            for (int i = 0; i <= K; i++) {
                for (int j = 0; j <= n; j++) {
                    f[i][j] = 1e15;
                }
            }
            f[0][0] = -1e15;
            for (int i = 1; i <= K; i++) {
                for (int j = i; j <= n; j++) {
                    for (int p = i - 1; p < j; p++) {
                        f[i][j] =
                            min(f[i][j], max(f[i - 1][p], sum[j] - sum[p]));
                    }
                }
            }
            for (int i = K; i <= n; i++) {
                ans = min(ans, f[K][i]);
            }
            printf("%lld\n", ans);
            continue;
        }
        if (K == 1) {
            ans = 1e15;
            for (int i = 1; i <= n; i++) {
                ans = min(ans, sum[i]);
            }
            printf("%lld\n", ans);
            continue;
        }
    }
    return 0;
}
