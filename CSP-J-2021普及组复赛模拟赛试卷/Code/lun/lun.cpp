#include <bits/stdc++.h>
using namespace std;

bool isValid(const string& account) {
    int N = account.length();
    int sum = 0;
    for(int i = N - 2; i >= 0; --i){
        int digit = account[i] - '0';
        if((N - 2 - i) % 2 == 0){
            digit *= 2;
            if(digit > 9){
                digit = digit / 10 + digit % 10;
            }
        }
        sum += digit;
    }
    int checksum = (sum * 9) % 10;
    int last_digit = account[N-1] - '0';
    return checksum == last_digit;
}

int main(){
    int N;
    cin >> N;
    string account;
    cin >> account;
    int pos = account.find('x');
    for(char d = '0'; d <= '9'; ++d){
        string temp = account;
        temp[pos] = d;
        if(isValid(temp)){
            cout << (d - '0') << endl;
            return 0;
        }
    }
    return 0;
}
