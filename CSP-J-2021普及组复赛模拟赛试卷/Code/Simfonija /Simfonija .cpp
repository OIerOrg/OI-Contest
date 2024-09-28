#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    cin >> N >> K;
    vector<int> A(N), B(N), C(N);
    for (auto &x : A)
        cin >> x;
    for (auto &x : B)
        cin >> x;
    for (int i = 0; i < N; i++)
        C[i] = B[i] - A[i];
    sort(C.begin(), C.end());
    vector<int> prefix_sum(N + 1, 0);
    for (int i = 1; i <= N; i++)
        prefix_sum[i] = prefix_sum[i - 1] + C[i - 1];
    int M = N - K;
    if (M == 0)
    {
        cout << 0;
        return 0;
    }
    int min_sum = LLONG_MAX;
    for (int l = 0; l + M <= N; l++)
    {
        int m = l + (M - 1) / 2;
        int Cm = C[m];
        int left = Cm * (m - l) - (prefix_sum[m] - prefix_sum[l]);
        int right = (prefix_sum[l + M] - prefix_sum[m + 1]) - Cm * (l + M - m - 1);
        min_sum = min(min_sum, left + right);
    }
    cout << min_sum;
}
