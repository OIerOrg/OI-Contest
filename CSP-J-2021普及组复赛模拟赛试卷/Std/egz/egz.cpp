/*能从 i 走到所有跑道相当于能从i走到 1 和 n,边反向后就相当于能从1和n走到i;
为了方便叙述,把1~n叫做 x 坐标,1~(m+1)叫做 y 坐标.
然后我们将图上下翻转(y坐标)后,能从1走到i的话一定会经过前 i-1 条向右的边,且这些边的 y 坐标不下降（从左往右看）.
那么我们设F[0][i]表示从 1 走到 i 最少加边数量,那么有 F[0][i]=i-1-LIS；
这里的 LIS 是 x 坐标在1~(i-1)的边的 y 坐标形成的最长不下降子序列长度.
LIS可以O(nlogn)预处理出来,同时我们反着处理一遍向左的边就能处理出从 n 走到 i 的最小加边数量F[1][i].
其实F[0][i]的值从左往右看是单调不降的，F[1][i]的值从右往左看也依然是单调不降的
最后一趟O(n)的枚举即可，因为F[1][i]单调不降(从后往前看)，所以再上一次的基础之上就OK；*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int n, m, p, k, Ans, T[maxn], F[2][maxn], son[2][maxn], nxt[2][maxn], lnk[2][maxn], cnt[2], opt[2][maxn];
int read() {
    int ret = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -f;
        ch = getchar();
    }
    while (isdigit(ch)) ret = (ret << 3) + (ret << 1) + ch - '0', ch = getchar();
    return ret * f;
}
void add_e(int a, int x, int y) {
    son[a][++cnt[a]] = y;
    nxt[a][cnt[a]] = lnk[a][x];
    lnk[a][x] = cnt[a];
}
void add(int x, int val) {
    for (; x <= m; x += x & -x) T[x] = max(T[x], val);
}
int Ask(int x) {
    int re = 0;
    for (; x; x -= x & -x) re = max(re, T[x]);
    return re;
}
int main() {
    freopen("egz.in", "r", stdin);
    freopen("egz.out", "w", stdout);
    n = read(), m = read() + 1, p = read(), k = read();
    for (int i = 1; i <= p; i++) {
        int x = read(), y = m - read(), z = read();
        if (z)
            add_e(0, x + 1, y);
        else
            add_e(1, x, y);
    }
    int LIS = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = lnk[0][i]; j; j = nxt[0][j]) LIS = max(LIS, opt[0][son[0][j]] = Ask(son[0][j]) + 1);
        F[0][i] = i - 1 - LIS;
        for (int j = lnk[0][i]; j; j = nxt[0][j]) add(son[0][j], opt[0][son[0][j]]);
    }
    memset(T, 0, sizeof T);
    LIS = 0;
    for (int i = n - 1; i; i--) {
        for (int j = lnk[1][i]; j; j = nxt[1][j]) LIS = max(LIS, opt[1][son[1][j]] = Ask(son[1][j]) + 1);
        F[1][i] = n - i - LIS;
        for (int j = lnk[1][i]; j; j = nxt[1][j]) add(son[1][j], opt[1][son[1][j]]);
    }
    int j = 1, now = 0;
    for (int i = 1; i <= n; i++) {
        while (j <= n && F[1][i] + F[0][j] <= k) j++; // 此处优化的原理F[1][i]>=F[1][i+1],故j从上一次继续就OK，满足i的所有j，依然满足i+1
        Ans = max(Ans, j - i); // 肯定挑选一块连续区间的大的啊
        if (!F[0][i] && !F[1][i]) now++; // 原本就可以到达的节点
    }
    printf("%d\n", Ans - now);
    return 0;
}
