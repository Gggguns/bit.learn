#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
#include <iostream>
#include<string>
using namespace std;

int main() {
    string str;
    while (getline(cin, str)) { // ע�� while ������ case
        for (auto& e : str)
        {
            if (e == ' ')continue;
            if (e - 'A' < 5)e = e + 21;
            else e -= 5;
        }
        cout << str << endl;
    }
}
// 64 λ������� printf("%lld")