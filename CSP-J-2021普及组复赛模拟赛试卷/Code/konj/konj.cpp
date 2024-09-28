#include <bits/stdc++.h>
using namespace std;
const int M = 305, N = 200005;
int mp[M][M], fa[N];
struct Line { int A, B, C, D; };
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(y)] = find(x); }

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, TX, TY; cin >> n;
    vector<Line> line(n + 1);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        int X1, Y1, X2, Y2; cin >> X1 >> Y1 >> X2 >> Y2;
        line[i] = {X1, Y1, X2, Y2};
        if (X1 == X2) if (Y1 > Y2) swap(Y1, Y2);
        for (int y = Y1; y <= Y2; y++) {
            if (mp[X1][y]) merge(mp[X1][y], i);
            mp[X1][y] = i;
        }
        if (Y1 == Y2) if (X1 > X2) swap(X1, X2);
        for (int x = X1; x <= X2; x++) {
            if (mp[x][Y1]) merge(mp[x][Y1], i);
            mp[x][Y1] = i;
        }
    }

    cin >> TX >> TY;
    vector<int> ve;
    for (int i = 1; i <= n; i++) {
        int X1 = line[i].A, Y1 = line[i].B, X2 = line[i].C, Y2 = line[i].D;
        if ((X1 == X2 && X1 == TX && Y1 <= TY && TY <= Y2) || 
            (Y1 == Y2 && Y1 == TY && X1 <= TX && TX <= X2)) {
            ve.push_back(i);
        }
    }
    if (ve.empty()) return 0;

    int target_root = find(ve[0]);
    for (auto seg : ve) target_root = find(seg);

    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    vector<int> connected_line;
    for (int i = 1; i <= n; i++)
        if (find(i) == target_root)
            connected_line.push_back(i);
    
    for (auto seg : connected_line) {
        minX = min(minX, min(line[seg].A, line[seg].C));
        maxX = max(maxX, max(line[seg].A, line[seg].C));
        minY = min(minY, min(line[seg].B, line[seg].D));
        maxY = max(maxY, max(line[seg].B, line[seg].D));
    }
    
    int width = maxX - minX + 1, height = maxY - minY + 1;
    vector<string> grid(height, string(width, '.'));
    
    for (auto seg : connected_line) {
        int A = line[seg].A - minX, B = line[seg].B - minY;
        int C = line[seg].C - minX, D = line[seg].D - minY;
        if (A == C)
            for (int y = min(B, D); y <= max(B, D); y++) grid[y][A] = '#';
        else
            for (int x = min(A, C); x <= max(A, C); x++) grid[B][x] = '#';
    }
    
    for (int y = height - 1; y >= 0; y--) cout << grid[y] << "\n";
    return 0;
}
