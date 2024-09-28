#include <bits/stdc++.h>
#define LL long long
#define maxn 100005
using namespace std;
int N, K, a[maxn], c[maxn];
LL S[maxn], Ans = (LL)1 << 62;
int read() {
    int ret = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
    while (isdigit(ch))
        ret = (ret << 3) + (ret << 1) + ch - '0', ch = getchar();
    return ret * f;
}
int main() {
    freopen("simfonija.in", "r", stdin);
    freopen("simfonija.out", "w", stdout);
    N = read(), K = N - read();
    for (int i = 1; i <= N; i++)
        a[i] = read();
    for (int i = 1; i <= N; i++)
        c[i] = read() - a[i];
    sort(c + 1, c + 1 + N);
    for (int i = 1; i <= N; i++)
        S[i] = S[i - 1] + c[i];
    for (int i = 1; i + K - 1 <= N; i++) {
        int Mid = 2 * i + K >> 1;
        LL now = (LL)c[Mid] * (Mid - i + 1) - (S[Mid] - S[i - 1]) +
                 (S[i + K - 1] - S[Mid]) - (LL)c[Mid] * (i + K - 1 - Mid);
        Ans = min(Ans, now);
    }
    printf("%lld\n", Ans);
    return 0;
}
