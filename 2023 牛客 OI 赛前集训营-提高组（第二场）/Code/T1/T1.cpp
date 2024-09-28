#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

long long qpow(long long base, long long exponent, long long mod) {
    base %= mod;
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}

int main() {
    int n;
    cin >> n;

    long long total_sum = n * (n + 1LL) / 2;
    vector<long long> cnt(total_sum + 1, 0);
    cnt[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (long long s = total_sum; s >= i; --s) {
            cnt[s] = (cnt[s] + cnt[s - i]) % (mod - 1);
        }
    }
    cnt[0] = 0;

    long long ans = 1;
    for (long long s = 1; s <= total_sum; ++s) {
        if (cnt[s]) {
            long long exponent = cnt[s] % (mod - 1);
            long long result = qpow(s, exponent, mod);
            ans = ans * result % mod;
        }
    }

    cout << ans;
    return 0;
}
