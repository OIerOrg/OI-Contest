#include<bits/stdc++.h>
using namespace std ;
int main() {
	int n , d;
	cin >> n >> d;
	vector<int> a(n + 1, 0);
	for(int i = 1; i <= n; i++)  cin >> a[i];
	vector<vector<int>> cnt(d, vector<int>(2, 0));
	for(int i = 1 ; i <= n; i++)
		cnt[i % d][a[i]] += 1;
	int mn = n;
	int one = count(a.begin() + 1, a.end(), 1);
	for(int i = 0; i < d; i++)
		mn = min(mn, one - cnt[i][1]);
	cout << mn << '\n';
}
