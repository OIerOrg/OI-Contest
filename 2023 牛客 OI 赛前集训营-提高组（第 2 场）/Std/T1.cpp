#include <bits/stdc++.h>
#define ll long long
const int N = 2e2 + 10;
const int mod = 998244353;
using namespace std;
ll dp[N * N];
ll qmi(ll a, ll n) {
    ll ans = 1;
    while (n)
        (ans *= n & 1 ? a : 1) %= mod, (a *= a) %= mod, n >>= 1;
    return ans;
}
signed main() {
    int n;
    cin >> n;
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = n * (n + 1) / 2; j - i >= 0; j--) {
            dp[j] += dp[j - i];
            dp[j] %= (mod - 1);
        }
    }
    ll ans = 1;
    for (int i = 1; i <= n * (n + 1) / 2; i++) {
        ans = (ans * qmi(i, dp[i])) % mod;
    }
    cout << ans << '\n';
}
