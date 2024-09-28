#include <bits/stdc++.h>
#define maxn 200005
#define N 305
using namespace std;
int n, x, y, cnt, a[maxn], b[maxn], c[maxn], d[maxn], son[6 * maxn],
    nxt[6 * maxn], lnk[91805], Q[maxn];
bool res[N][N], vis[91805];
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
void add_e(int x, int y) {
    son[++cnt] = y;
    nxt[cnt] = lnk[x];
    lnk[x] = cnt;
}
void Draw(int x, int y, int x_, int y_) {
    if (x > x_)
        swap(x, x_);
    if (y > y_)
        swap(y, y_);
    for (int i = x; i <= x_; i++)
        for (int j = y; j <= y_; j++)
            res[i][j] = 1;
}
void BFS() {
    vis[Q[1] = x * N + y] = 1;
    int hed = 0, til = 1;
    while (hed != til) {
        int x = Q[hed = (hed + 1) % maxn];
        for (int j = lnk[x]; j; j = nxt[j]) {
            Draw(x / N, x % N, son[j] / N, son[j] % N);
            if (!vis[son[j]])
                vis[son[j]] = 1, Q[til = (til + 1) % maxn] = son[j];
        }
    }
}
int main() {
    freopen("konj.in", "r", stdin);
    freopen("konj.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read(), b[i] = read(), c[i] = read(), d[i] = read();
    x = read(), y = read();
    for (int i = 1; i <= n; i++) {
        if (a[i] > c[i])
            swap(a[i], c[i]);
        if (b[i] > d[i])
            swap(b[i], d[i]);
        if (a[i] <= x && x <= c[i] && b[i] <= y && y <= d[i]) {
            add_e(x * N + y, a[i] * N + b[i]),
                add_e(a[i] * N + b[i], x * N + y);
            add_e(x * N + y, c[i] * N + d[i]),
                add_e(c[i] * N + d[i], x * N + y);
        }
        add_e(a[i] * N + b[i], c[i] * N + d[i]),
            add_e(c[i] * N + d[i], a[i] * N + b[i]);
    }
    BFS();
    int X = 0, Y = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (res[i][j])
                X = max(X, i), Y = max(Y, j);
    int A = N, B = N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (res[i][j])
                A = min(A, i), B = min(B, j);
    for (int j = Y; j >= B; j--)
        for (int i = A; i <= X; i++) {
            char ch = res[i][j] ? '#' : '.';
            if (i == X)
                printf("%c\n", ch);
            else
                printf("%c", ch);
        }
    return 0;
}
