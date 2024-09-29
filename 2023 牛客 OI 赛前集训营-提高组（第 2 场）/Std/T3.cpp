#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i <= y; ++i)
#define repd(i, x, y) for (int i = x; i >= y; --i)
#define mid ((l + r) >> 1)
#define lch (rt << 1)
#define rch (rt << 1 | 1)
#define pb push_back

using namespace std;
typedef long long LL;
const int N = 100005, M = 52;
const LL INF = 1e18;
bool vis[N], mp[M][M];
int n, a[N], k, m, id[N];
LL ans, f[N][M];
struct D {
    int u, v;
} dat[M];
vector<int> vt[N];

int getint() {
    char ch;
    int f = 1;
    while (!isdigit(ch = getchar()))
        if (ch == '-')
            f = -1;
    int x = ch - 48;
    while (isdigit(ch = getchar()))
        x = x * 10 + ch - 48;
    return x * f;
}

void dfs(int x) {
    rep(i, 0, k) f[x][i] = -INF;
    f[x][id[x]] = a[x];
    for (auto v : vt[x]) {
        dfs(v);
        LL mx = -INF;
        rep(i, 0, k) if (!mp[i][id[v]]) mx = max(mx, f[x][i]);
        rep(i, 0, k) f[x][i] = max(f[x][i], f[v][i] + mx);
    }
    rep(i, 0, k) ans = max(ans, f[x][i]);
}
int main() {
    cin >> n >> m;
    rep(i, 1, n) scanf("%d", a + i);
    ans = a[1];
    rep(i, 2, n) ans = max(ans, (LL)a[i]);
    if (ans <= 0)
        return printf("%lld\n", ans), 0;
    rep(i, 1, n) {
        int x, k;
        scanf("%d", &k);
        while (k--) {
            scanf("%d", &x);
            vt[i].pb(x);
        }
    }
    rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        dat[i] = (D){u, v};
        vis[u] = vis[v] = 1;
    }
    rep(i, 1, n) if (vis[i]) id[i] = ++k;
    memset(vis, 0, sizeof(vis));
    rep(i, 1, m) {
        int u = id[dat[i].u], v = id[dat[i].v];
        mp[u][v] = mp[v][u] = 1;
    }
    dfs(1);
    printf("%lld\n", ans);
}
