// 80 ~ 100
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
const int LG = 24;
int arr[N], Last[N], Next[N], ST[N][LG];
unsigned long long ans;
int query(int l, int r)
{
	int k = log2(r - l + 1);
	return max(ST[l][k], ST[r - (1 << k) + 1][k]);
}
int main()
{
	freopen("T1.in", "r", stdin);
	freopen("T1.out", "w", stdout);
	int n, m;
	scanf("%d", &n);
	m = log2(n);
	for (int i(1); i <= n; ++i)
		scanf("%d", arr + i);
	stack<int> st;
	for (int i(1); i <= n; ++i)
	{
		while (!st.empty() && arr[st.top()] >= arr[i])
			st.pop();
		Last[i] = (st.empty() ? -1 : st.top());
		st.push(i);
	}
	while (!st.empty()) st.pop();
	for (int i(n); i >= 1; --i)
	{
		while (!st.empty() && arr[st.top()] >= arr[i])
			st.pop();
		Next[i] = (st.empty() ? -1 : st.top());
		st.push(i);
	}
	for (int i(1); i <= n; ++i)
		ST[i][0] = arr[i];
	for (int i(1); i <= m; ++i)
	{
		for (int j = 1; j <= n - (1 << i) + 1; j++)
		{
			ST[j][i] = max(ST[j][i - 1], ST[j + (1 << (i - 1))][i - 1]);
		}
	}
	for (int i(1); i <= n; ++i)
	{	
		int L = (Last[i] == -1 ? 1 : Last[i] + 1);
		int R = (Next[i] == -1 ? n : Next[i] - 1);
		ans = max(ans, 1ULL * query(L, R) * arr[i] * (R - L + 1));
	}
	printf("%llu\n", ans);
	fprintf(stderr, "Time used: %.2lf s\n", (double)clock() / CLOCKS_PER_SEC);
	return 0;
}
/*
1. 枚举最小值
2. 单调栈求解小于当前值且在其之前的最后一个数
3. 单调栈求解小于当前值且在其之后的第一个数
4. ST 表预处理 [i, j] 的最大值
9
5 11 15 17 19 3 19 9 4
*/