#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
typedef long long LL;
#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define Rof(i, a, b) for (int i = (a); i >= (b); --i)
void file() {
    freopen("hire.in", "r", stdin);
    freopen("hire.out", "w", stdout);
}
struct Info {
    LL ls, rs, s, ans;
    Info operator+(const Info x) {
        return {max(ls, s + x.ls), max(x.rs, x.s + rs), s + x.s,
                max({ans, x.ans, rs + x.ls})};
    }
} t[N << 2];
int n, m;
LL k, d;
void Mod(int p, LL v, int c, int l, int r) {
    if (l == r) {
        t[c].s += v;
        t[c].ls = t[c].rs = t[c].ans = max(t[c].s, 0LL);
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid)
        Mod(p, v, c << 1, l, mid);
    else
        Mod(p, v, c << 1 | 1, mid + 1, r);
    t[c] = t[c << 1] + t[c << 1 | 1];
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> k >> d, n -= d, d *= k;
    For(i, 1, n) Mod(i, -k, 1, 1, n);
    For(_, 1, m) {
        int x, y;
        cin >> x >> y, Mod(x, y, 1, 1, n);
        cout << (t[1].ans > d ? "NO" : "YES") << '\n';
    }
    return 0;
}