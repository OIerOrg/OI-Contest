#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10, M = 31;
ll a[N], dp[N][M], Tmp[M];
int L[N], R[N];
vector<int> E[N];
bool T[M][M];
int m;
void Dp(int cur) {
    dp[cur][L[cur]] = max(dp[cur][L[cur]], a[cur]);
    for (int to : E[cur]) {
        Dp(to);
        memcpy(Tmp, dp[cur], sizeof(dp[cur]));
        for (int p = 0; p <= m; ++p) {
            for (int j = 0; j <= m; ++j) {
                if (!T[j][R[to]])
                    dp[cur][p] = max(Tmp[j] + dp[to][p], dp[cur][p]);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    // freopen("tree.in","r",stdin);
    int n;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        E[i].resize(k);
        for (int j = 0; j < k; ++j)
            cin >> E[i][j];
    }
    for (int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        if (!L[l])
            L[l] = i;
        if (!R[r])
            R[r] = i;
        T[L[l]][R[r]] = true;
    }
    memset(dp, 0xcf, sizeof(dp));
    Dp(1);
    ll Ans = 0;
    for (int i = 0; i <= m; ++i)
        Ans = max(Ans, dp[1][i]);
    cout << Ans << "\n";
    return 0;
}