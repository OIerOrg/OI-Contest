#include <bits/stdc++.h>

using namespace std;

#define lep(i, l, r) for (int i = (l); i <= (r); i++)
#define rep(i, l, r) for (int i = (l); i >= (r); i--)

const int N = 500 + 5;
const int P = 1e9 + 7;

inline int mod(int x) { return x + (x >> 31 & P); }
inline void pls(int &x, int y) { x = mod(x + y - P); }

int power(int x, int k) {
    int res = 1;
    while (k) {
        if (k & 1)
            res = 1ll * res * x % P;
        x = 1ll * x * x % P;
        k >>= 1;
    }
    return res;
}

int n;
int F[N][N][2], G[N][N][2];
char str[N];

int fac[N], ifac[N];
inline int C(int x, int y) {
    if (x < 0 || y < 0 || x < y)
        return 0;
    return 1ll * fac[x] * ifac[y] % P * ifac[x - y] % P;
}

int main() {
    //	freopen("checkers.in", "r", stdin);
    //	freopen("checkers.out", "w", stdout);
    //	ios :: sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    cin >> (str + 1);
    auto f = F;
    auto g = G;
    f[0][0][0] = 1;
    lep(i, 1, n) {
        memset(g, 0, sizeof(G));
        lep(j, 0, i) lep(k, 0, i) lep(op, 0, 1) if (f[j][k][op]) {
            char ch = str[i];
            if (ch == '0' || ch == '?')
                pls(g[j][k + 1][0], f[j][k][op]);
            if (ch == '1' || ch == '?') {
                if (op == 1)
                    pls(g[j + 1][k][0], f[j][k][op]);
                else
                    pls(g[j][k][1], f[j][k][op]);
            }
        }
        swap(f, g);
    }
    fac[0] = 1;
    lep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % P;
    ifac[n] = power(fac[n], P - 2);
    rep(i, n - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
    int ans = 0;
    lep(i, 0, n) lep(j, 0, n) if (f[i][j][0] || f[i][j][1]) {
        int res = mod(f[i][j][0] + f[i][j][1] - P);
        ans = (ans + 1ll * res * C(i + j, i)) % P;
    }
    printf("%d\n", ans);
    return 0;
}
