#include <bits/stdc++.h>
using namespace std;
bool check (string s, int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (i & 1) {
            sum += s[i] - '0';
        } else {
            int x = s[i] - '0'; x *= 2;
            if (x <= 9) sum += x;
            else sum += x % 10 + 1;
        }
    }
    if (sum * 9 % 10 == s[n] - '0') return true;
    else return false;
}
int main()
{
    int n; string s;
    cin >> n >> s; s = " " + s;
    int id;
    for (int i = 1; i <= n; i++)
        if (s[i] == 'x')
        {
            id = i;
            break;
        }
    for (char i = '0'; i <= '9'; i++) {
        s[id] = i;
        if (check(s, n)) {
            cout << i;
            return 0;
        }
    }
}