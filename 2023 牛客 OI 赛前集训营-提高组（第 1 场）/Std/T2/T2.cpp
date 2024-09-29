#include <bits/stdc++.h>

using namespace std;

namespace IO {
	const int N = 2e6;
	char buf[N], *p1 = buf, *p2 = buf;
	inline char gc() {
		if(p1 == p2) p2 = (p1 = buf) + fread(buf, 1, N, stdin);
		return p1 == p2 ? EOF : *(p1 ++);
	}
	inline int read() {
		int x = 0, f = 1; char a = gc();
		for(; !isdigit(a); a = gc()) if(a == '-') f = -1;
		for(; isdigit(a); a = gc()) x = x * 10 + (a ^ 48);
		return x * f;
	}
	char Of[105], *O1 = Of, *O2 = Of;
	template <typename T>
	inline void print(T n, char ch = '\n') {
		if(n < 0) putchar('-'), n = -n;
		if(n == 0) putchar('0');
		while(n) *(O1 ++) = (n % 10) ^ 48, n /= 10;
		while(O1 != O2) putchar(*(-- O1));
		putchar(ch);
	}
}

using IO :: read;
using IO :: print;

#define lep(i, l, r) for(int i = (l); i <= (r); i ++)
#define rep(i, l, r) for(int i = (l); i >= (r); i --)

const int N = 1e6 + 5;

struct Tree {
	#define lowbit(x) (x & -x)
	int c[N], d[N];
	void add(int y) {
		assert(y);
		for(int x = y; x < N; x += lowbit(x)) c[x] += y, d[x] ++;
	}
	void ers(int y) {
		assert(y);
		for(int x = y; x < N; x += lowbit(x)) c[x] -= y, d[x] --;
	}
	pair<int, int> qry(int k) {
		int x = 0, ans = 0; 
		rep (i, 20, 0) if(x + (1 << i) < N && k >= c[x + (1 << i)]) {
			k -= c[x + (1 << i)], ans += d[x + (1 << i)], x += (1 << i); 
		}
		ans += k / (x + 1);
		k %= (x + 1);
		return {ans, k};
	}
} T[2];

int n, m, q;
int a[N], t[2];
set<int> st;
int res, pir;

void query() {
	if(st.size() == 2) {
		if(t[0] >= n || t[1] >= n) { print(0); return ; }
		print(1); return ;
	}
	int ans = pir * 2 + res;
	static int stk[5], top;
	top = 0;
	if(a[1] == 0) {
		auto it = ++ st.begin();
		int len = (* it) - 1;
		assert(len);
		T[a[0] & 1].ers(len);
		stk[++ top] = (a[* it] & 1);
		stk[++ top] = - len;
		ans --;
	}
	if(a[n] == 0) {
		auto it = -- st.end(); -- it;
		int len = n - (* it);
		assert(len);
		T[a[* it] & 1].ers(len);
		stk[++ top] = (a[* it] & 1);
		stk[++ top] = len;
		ans --;
	}
	auto p2 = T[0].qry(t[0]), p1 = T[1].qry(t[1]);
	ans -= p1.first * 2;
	ans -= p2.first * 2;
	while(top) {
		int flg = 0;
		if(stk[top] < 0) flg = 1, stk[top] = - stk[top];
		if(stk[top - 1]) {
			if(p1.second >= stk[top]) p1.second -= stk[top], ans --;
		}
		else {
			if(p2.second >= stk[top]) p2.second -= stk[top], ans --;
		}
		if(! flg) T[stk[top - 1]].add(stk[top]);
		else T[0].add(stk[top]);
		top -= 2;
	}
	print(ans);
}

int main() {
	freopen("drawing.in", "r", stdin);
	freopen("drawing.out", "w", stdout);
	n = read(), m = read(), q = read(); 
	st.insert(0); st.insert(n + 1);
	lep (i, 1, n) t[read() & 1] ++;
	lep (i, 1, m){
		int p = read(), v = read();
		a[p] = v, st.insert(p), t[v & 1] --;
	}
	auto Push_Seg = [] (auto itl, auto itr) {
		if((* itl) + 1 < * itr) {
			if((* itl) == 0 || (* itr) == n + 1 || ((a[* itl] & 1) == (a[* itr] & 1))) {
				T[a[* itl] & 1].add((* itr) - (* itl) - 1);
				pir ++;
			} 
			else res ++;
		}
		else {
			if((* itl) == 0 || (* itr) == n + 1 || ((a[* itl] & 1) == (a[* itr] & 1))) return ;
			else res ++;
		}
	} ;
	auto Pop_Seg = [] (auto itl, auto itr) {
		if((* itl) + 1 < * itr) {
			if((* itl) == 0 || (* itr) == n + 1 || ((a[* itl] & 1) == (a[* itr] & 1))) {
				T[a[* itl] & 1].ers((* itr) - (* itl) - 1);
				pir --;
			} 
			else res --;
		}
		else {
			if((* itl) == 0 || (* itr) == n + 1 || ((a[* itl] & 1) == (a[* itr] & 1))) return ;
			else res --;
		}
	} ;
	for(auto itr = ++ st.begin(), itl = st.begin(); itr != st.end(); itl = itr, ++ itr) {
		Push_Seg(itl, itr);
	}
	auto Add = [&] (int pos, int v) {
		auto itr = st.lower_bound(pos);
		auto itl = itr; itl --;
		Pop_Seg(itl, itr);
		st.insert(pos);
		a[pos] = v;
		auto it = st.lower_bound(pos); itl = it, itr = it;
		itl --; itr ++;
		Push_Seg(itl, it);
		Push_Seg(it, itr);
	} ;
	auto Dec = [&] (int pos) {
		auto it = st.lower_bound(pos);
		auto itl = it, itr = it;
		itl --; itr ++;
		Pop_Seg(itl, it); Pop_Seg(it, itr);
		a[pos] = 0;
		Push_Seg(itl, itr);
		st.erase(it);
	} ;
	while(q --) {
		int op = read(), p = read(), v;
		if(op == 1) ++t[a[p] & 1], Dec(p);
		else v = read(), Add(p, v), --t[a[p] & 1];
		query();
	}
	return 0;
}
