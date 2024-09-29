#include <bits/stdc++.h>
#define R register
#define LL long long
using namespace std;
char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar()                                                              \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)   \
         ? EOF                                                                 \
         : *p1++)
inline int read() {
    int x = 0, d = 1;
    char y = getchar();
    for (; y < '0' || y > '9'; y = getchar())
        if (y == '-')
            d = -1;
    for (; y >= '0' && y <= '9'; y = getchar())
        x = (x << 3) + (x << 1) + (y ^ '0');
    return x * d;
}
const int N = 2e6 + 10;
int n, m, k, d;
LL sum[N], lmax[N], rmax[N], maxn[N];
void push_up(int t) {
    int ls = t << 1, rs = (t << 1) | 1;
    sum[t] = sum[t << 1] + sum[(t << 1) | 1];
    lmax[t] = max(lmax[ls], sum[ls] + lmax[rs]);
    rmax[t] = max(rmax[rs], sum[rs] + rmax[ls]);
    maxn[t] = max(max(maxn[ls], maxn[rs]), rmax[ls] + lmax[rs]);
}
void push_x(int t, int x) {
    sum[t] += x;
    lmax[t] = rmax[t] = maxn[t] = sum[t];
}
void build(int l, int r, int t) {
    if (l == r) {
        push_x(t, -k);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, t << 1);
    build(mid + 1, r, (t << 1) | 1);
    push_up(t);
}
void modify(int l, int r, int t, int x, int y) {
    if (l == r) {
        push_x(t, y);
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= x)
        modify(l, mid, t << 1, x, y);
    else
        modify(mid + 1, r, (t << 1) | 1, x, y);
    push_up(t);
}
int main() {
    freopen("lantern.in", "r", stdin);
    freopen("lantern.out", "w", stdout);
    n = read();
    m = read();
    k = read();
    d = read();
    build(1, n - d, 1);
    for (R int i = 1, x, y; i <= m; i++) {
        x = read();
        y = read();
        modify(1, n - d, 1, x, y);
        if (maxn[1] <= 1ll * k * d)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
