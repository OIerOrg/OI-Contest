#include <bits/stdc++.h>
using namespace std;
int N, Num[105], pos;
bool check() {
    int sum = 0;
    for (int i = 2; i <= N; i++)
        if (i & 1)
            sum += Num[i];
        else
            sum += (Num[i] << 1) % 10 + (Num[i] << 1) / 10;
    sum *= 9;
    return sum % 10 == Num[1];
}
int main() {
    freopen("lun.in","r",stdin);
    freopen("lun.out","w",stdout);
    cin >> N;
    getchar();
    for (int i = 1; i <= N; i++) {
        char ch = getchar();
        if (ch == 'x')
            pos = N + 1 - i;
        else
            Num[N + 1 - i] = ch - '0';
    }
    for (int i = 0; i < 10; i++) {
        Num[pos] = i;
        if (check()) {
            printf("%d\n", i);
            return 0;
        }
    }
}
