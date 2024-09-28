#include <bits/stdc++.h>

using std :: cin;
using std :: cout;
using std :: cerr;

#define endl '\n'

using i64 = long long;

const int N = 3e5 + 5;
const int LIM = 100;
const int B = 175;

int n, m;

namespace BigTree {

	std :: vector<std :: pair<int, int> > e[N << 1];
	
	void push(int x, int y, int w) {
		e[x].push_back({y, w});
		e[y].push_back({x, w});
	}
	
	int st[N << 1][20], lg[N << 1], sz[N], tdfn[N];
	int dfn[N], num; int dep[N];
	i64 dis[N];

	void dfs(int x, int fx) {
		dfn[x] = ++ num; dep[x] = dep[fx] + 1;
		st[num][0] = x; sz[x] = 1; tdfn[x] = ++ tdfn[0];
		for(auto p : e[x]) if(p.first != fx) {
			dis[p.first] = dis[x] + p.second;
			dfs(p.first, x);
			st[++ num][0] = x;
			sz[x] += sz[p.first];
		}
	}

	void build() {
		for(int i = 2; i <= (n << 1); i ++) lg[i] = lg[i >> 1] + 1;
		dfs(1, 0);
		for(int i = 1; (1 << i) <= (n << 1); i ++)
			for(int j = 1; j + (1 << i) - 1 <= (n << 1); j ++) 
				if(dep[st[j][i - 1]] < dep[st[j + (1 << (i - 1))][i - 1]])
					st[j][i] = st[j][i - 1];
				else
					st[j][i] = st[j + (1 << (i - 1))][i - 1];
	}

	inline int lca(int x, int y) {
		x = dfn[x]; y = dfn[y];
		if(x > y) std :: swap(x, y);
		int d = lg[y - x + 1];
		return dep[st[x][d]] < dep[st[y - (1 << d) + 1][d]] ? st[x][d] : st[y - (1 << d) + 1][d];
	}

	inline i64 dist(int x, int y) {
		return dis[x] + dis[y] - dis[lca(x, y)] * 2;
	}

	inline int isfa(int x, int y) {
		return tdfn[x] <= tdfn[y] && tdfn[y] <= tdfn[x] + sz[x] - 1;
	}
}

using BigTree :: dfn;
using BigTree :: lca;
using BigTree :: dist;
using BigTree :: dis;
using BigTree :: isfa;

namespace VirtualTree {
	int vis[N], fa[N], son[N];
	i64 len[N], val[N];
	std :: vector<std :: pair<int, i64> > e[N];

	void dfs(int x, int fx) {
		fa[x] = fx; son[x] = 0; 
		for(auto p : e[x]) {
			int y = p.first;
			i64 w = p.second;
			if(y == fx) continue;
			val[y] = w;
			dfs(y, x);
			if(len[y] + w >= len[son[x]] + val[son[x]]) son[x] = y;
		}
		len[x] = (! son[x]) ? 0 : val[son[x]] + len[son[x]];
	}

	std :: vector<std :: pair<int, i64> > build(std :: vector<int> &v) {

//////////////////////////////////////////////////////////////////////////////////////////////////////////

		std :: sort(v.begin(), v.end(), [&] (int a, int b) { return dfn[a] < dfn[b]; } );
		std :: vector<int> pv(v.size() + v.size() - 1);
		int cnt = 0;
		for(int i = 0; i < (int) v.size() - 1; i ++) pv[cnt ++] = lca(v[i], v[i + 1]);
		
		for(int x : v) pv[cnt ++] = x;
		std :: sort(pv.begin(), pv.end());
		pv.erase(std :: unique(pv.begin(), pv.end()), pv.end());
		std :: sort(pv.begin(), pv.end(), [&] (int a, int b) { return dfn[a] < dfn[b]; });

		for(int x : pv) e[x].clear();
		
		static int stk[N], top;
		stk[top = 1] = pv[0];
		int rt = pv[0];

		for(int i = 1; i < pv.size(); i ++) {
			int x = pv[i];
			while(top > 1 && ! isfa(stk[top], x)) {
				int u = stk[top - 1];
				int v = stk[top];
				e[u].push_back({v, dis[v] - dis[u]});
				e[v].push_back({u, dis[v] - dis[u]});
				top --;
			}
			stk[++ top] = x;
		}
		while(top > 1 ) {
			int u = stk[top - 1];
			int v = stk[top];
			e[u].push_back({v, dis[v] - dis[u]});
			e[v].push_back({u, dis[v] - dis[u]});
			top --;
		}

////////////////////////////////////////////////////////

		static i64 Dis[N];
		static bool Vis[N];
		
		for(int x : pv) Vis[x] = 0;

		std :: queue<int> q;
		q.push(rt); Dis[rt] = 0;
		Vis[rt] = 1;
		while(q.size()) {
			int x = q.front(); q.pop();
			for(auto p : e[x]) {
				int y = p.first;
				i64 w = p.second;
				if(Vis[y]) continue;
				Vis[y] = 1;
				Dis[y] = Dis[x] + w;
				q.push(y);
			}
		}

		rt = 0;  i64 mx = -5;
		for(int x : v) if(Dis[x] >= mx) mx = Dis[x], rt = x;

		dfs(rt, 0);
		val[rt] = 0;
		std :: sort(pv.begin(), pv.end(), [&] (int a, int b) -> bool {
			if(a == rt) return 1;
			return len[a] + val[a] > len[b] + val[b];
		} );
		
		std :: vector<std :: pair<int, i64> > rec;
		std :: vector<int> temp;
		rec.push_back({rt, 0ll});

		for(int x : pv) vis[x] = 1;
		i64 ans = 0; 
		for(int x : pv) {
			if(rec.size() >= LIM) break;
			if(vis[x] == 0) { temp.push_back(x); continue; }
			int t = x;
			ans += len[x] + val[x];
			vis[x] = 0;
			while(son[x]) {
				x = son[x];
				vis[x] = 0;
			}
			rec.push_back({x, ans});
		}
		cnt = 0;
		while(rec.size() < v.size() && rec.size() < LIM) {
			rec.push_back( {temp[cnt ++], ans} );
		}
		return rec;
	}
}

using set = std :: vector<std :: pair<int, i64> >;

set merge(set &a, set &b) {
	std :: vector<int> res(a.size() + b.size());
	for(int i = 0; i < a.size(); i ++) res[i] = a[i].first;
	for(int i = 0; i < b.size(); i ++) res[a.size() + i] = b[i].first;
	return VirtualTree :: build(res);
}

set st[N / B][17];
int lg[N], a[N];

inline int bel(int x) { return (x - 1) / B + 1; }

inline i64 query(int l, int r, int k) {
	int LD = bel(l), RD = bel(r);
	static int stk[N]; int top = 0;
	if(LD == RD) {
		for(int i = l; i <= r; i ++) stk[++ top] = a[i];
	}
	else {
		for(int i = l; i <= LD * B; i ++) stk[++ top] = a[i];
		for(int i = (RD - 1) * B + 1; i <= r; i ++) stk[++ top] = a[i];
		l = LD + 1; r = RD - 1;
		if(l <= r) {
			int d = lg[r - l + 1];
			set &L = st[l][d];
			set &R = st[r - (1 << d) + 1][d];
			for(auto p : L) stk[++ top] = p.first;
			for(auto p : R) stk[++ top] = p.first;
		}
	}
	std :: vector<int> v(stk + 1, stk + 1 + top);
	auto res = VirtualTree :: build(v);
	return res[k - 1].second;
}

inline void decode(int &l, int &r, int &k, i64 lstans, int testop) {
	lstans %= 19260817;
	if(testop) {
		l ^= lstans; l = (l % n + n) % n + 1;
		r ^= lstans; r = (r % n + n) % n + 1;
		if(l > r) std :: swap(l, r);
		k ^= lstans; 
		k = (k % std :: min(r - l + 1, 100)) + 1;
	}
}

int testop;

signed main() {
//	freopen("nomenclature.in", "r", stdin);
//	freopen("nomenclature.out", "w", stdout);
//	std :: ios :: sync_with_stdio(false);
//	cin.tie(0); cout.tie(0);
	int nonono;
	cin >> nonono;
	cin >> testop >> n;
	for(int i = 1, x, y, w; i <= n - 1; i ++) {
		cin >> x >> y >> w;
		BigTree :: push(x, y, w);
	}
	BigTree :: build();
	for(int i = 1; i <= n; i ++) cin >> a[i];
	
	for(int i = 2; i <= n; i ++) lg[i] = lg[i >> 1] + 1;
	int tot = (n - 1) / B + 1;
	for(int i = 1; i <= n; i += B) {
		int l = i;
		int r = std :: min(i + B - 1, n);
		std :: vector<int> vec(a + l, a + r + 1);
		st[(i - 1) / B + 1][0] = VirtualTree :: build(vec);
	}
	for(int i = 1; (1 << i) <= tot; i ++)
		for(int j = 1; j + (1 << i) <= tot; j ++)
			st[j][i] = merge(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]); 
	//return 0;
	int Q; cin >> Q; 
	i64 lstans = 0; 
	while(Q --) {
		int l, r, k; cin >> l >> r >> k;
		decode(l, r, k, lstans, testop);
		lstans = query(l, r, k); 
		cout << lstans << endl;
	}
    return 0;
}
