// 100
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int cnt[N], Cnt, Max;
signed main() {
    freopen("T3.in", "r", stdin);
    freopen("T3.out", "w", stdout);
    int n, d;
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        if (x == 1) {
            cnt[i % d]++, Cnt++;
        }
    }
    for (int i = 0; i < d; i++)
        Max = max(cnt[i], Max);
    cout << Cnt - Max << endl;
    return 0;
}