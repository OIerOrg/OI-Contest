#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    long long ans = 0;
    scanf("%d%d", &n, &m);
    vector<int> a(n), b(m);
    for (int &i : a)
        cin >> i;
    for (int &i : b)
        cin >> i;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    while (a.size() && b.size() && a.back() > 0 && b.back() > 0) {
        ans += 1LL * a.back() * b.back();
        a.pop_back();
        b.pop_back();
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    while (a.size() && b.size() && a.back() < 0 && b.back() < 0) {
        ans += 1LL * a.back() * b.back();
        a.pop_back();
        b.pop_back();
    }
    sort(a.begin(), a.end());
    if (b[0] < 0)
        sort(b.begin(), b.end());
    if (b[0] > 0)
        sort(b.begin(), b.end(), greater<int>());
    while (b.size() > a.size())
        b.pop_back();
    sort(b.begin(), b.end(), greater<int>());
    for (int i = 0; i < a.size(); i++)
        ans += 1LL * a[i] * b[i];

    printf("%lld", ans);
    return 0;
}
