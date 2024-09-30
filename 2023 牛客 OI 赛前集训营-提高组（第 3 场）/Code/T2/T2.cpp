#include <algorithm>
#include <iostream>
#include <vector>
#define int long long
using namespace std;

const int N = 1e7 + 10; // 增大数组大小以适应线段树节点
int ls[N], rs[N], cnt[N], sum[N], Cnt;

// 插入元素到线段树
inline void update(int &o, int l, int r, int id) {
    if (!o)
        o = ++Cnt;
    if (l == r) {
        cnt[o]++;
        sum[o] += id;
        return;
    }
    int mid = (l + r) >> 1;
    if (id <= mid)
        update(ls[o], l, mid, id);
    else
        update(rs[o], mid + 1, r, id);
    cnt[o] = cnt[ls[o]] + cnt[rs[o]];
    sum[o] = sum[ls[o]] + sum[rs[o]];
}
// 查询满足条件的元素数量
inline void query(int o, int l, int r, int &leftover, int &ans) {
    if (!o)
        return;
    if (sum[o] <= leftover) {
        ans += cnt[o];
        leftover -= sum[o];
        return;
    }
    if (l == r) { // 处理叶子节点
        int possible = min(cnt[o], leftover / l);
        ans += possible;
        leftover -= possible * l;
        return;
    }
    int mid = (l + r) >> 1;
    query(ls[o], l, mid, leftover, ans);
    if (leftover > 0)
        query(rs[o], mid + 1, r, leftover, ans);
}

signed main() {
    int testcase;
    scanf("%lld", &testcase);
    while (testcase--) {
        // 重置线段树
        for (int i(1); i <= Cnt; ++i)
            ls[i] = rs[i] = cnt[i] = sum[i] = 0;
        Cnt = 0;
        int root = 0; // 为当前测试用例初始化根节点

        int n, m, x;
        scanf("%lld%lld", &n, &m);
        for (int i(1); i <= n; ++i) {
            scanf("%lld", &x);
            int ans = 0;
            int leftover = m - x;
            if (leftover >= 0) { // 确保 leftover 为非负
                query(root, 1, 1e9, leftover, ans);
            }
            printf("%lld ", i - ans - 1);
            update(root, 1, 1e9, x);
        }
        putchar('\n');
    }
    return 0;
}
