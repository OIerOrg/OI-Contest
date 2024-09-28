#include <bits/stdc++.h>
 
using namespace std;
 
using pii = pair<int, int>;
using i64 = long long;
//using i128 = __int128;
using uint = unsigned int;
using ui64 = unsigned long long;
 
namespace IO {
	char a; int f;
	template<typename T> inline void read(T &x) {
		x = 0; f = 1; a = getchar();
		for(; ! isdigit(a); a = getchar()) if(a == '-') f = -1;
		for(; isdigit(a); a = getchar()) x = x * 10 + a - '0';
		x *= f;
	}
	template <typename T> inline void write(T x) {
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
	int read() { int x; read(x); return x; }
	i64 read64() { i64 x; read(x); return x; }
} 
 
using IO :: read;
using IO :: write;
using IO :: read64;
 
const int P = 998244353;
inline int mod(int x) { return x + ((x >> 31) & P); }
inline void pls(int &x, int y) { x = mod(x + y - P); }
inline void dec(int &x, int y) { x = mod(x - y); }
inline int power(int x, int k) {
	int res = 1;
	while(k) {
		if(k & 1) res = 1ll * res * x % P;
		x = 1ll * x * x % P; k >>= 1;
	} return res;
}
 
#define lep(i, l, r) for(int i = (l); i <= (r); i ++)
#define rep(i, l, r) for(int i = (l); i >= (r); i --)
 
const int N = 2e6 + 10;

int n, ls[N], rs[N], fa[N], val[N], stk[N], top;
int mn[N], sz[N], mx[N];

__int128 ans;

void dfs(int x) {
	sz[x] = 1; mn[x] = val[x]; mx[x] = val[x];
	if(ls[x]) dfs(ls[x]), sz[x] += sz[ls[x]], mn[x] = min(mn[x], mn[ls[x]]), mx[x] = max(mx[x], mx[ls[x]]);
	if(rs[x]) dfs(rs[x]), sz[x] += sz[rs[x]], mn[x] = min(mn[x], mn[rs[x]]), mx[x] = max(mx[x], mx[rs[x]]);
	__int128 res = sz[x];
	res *= mn[x];
	res *= mx[x];
	ans = max(ans, res);
}

signed main() {
	freopen("sitcom.in", "r", stdin);
	freopen("sitcom.out", "w", stdout);
	scanf("%d", &n);
	lep (i, 1, n) scanf("%lld", &val[i]);
	lep (i, 1, n) {
		int pos = top;
		while(pos && val[stk[pos]] > val[i]) pos --;
		if(pos) rs[stk[pos]] = i, fa[i] = stk[pos];
		if(pos < top) ls[i] = stk[pos + 1], fa[stk[pos + 1]] = i;
		stk[top = ++ pos] = i;
	}
	int rt = 0;
	lep (i, 1, n) if(! fa[i]) rt = i;
	dfs(rt);
	write(ans); putchar('\n');
	return 0;
}
