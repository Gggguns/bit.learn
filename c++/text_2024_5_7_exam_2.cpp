#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<vector>
using namespace std;

int main() {
    long long n = 0, Max = -0xffffff, Sum = 0, left = -1, right = 0;
    cin >> n;
    vector<long long> v(n);
    for (long long i = 0;i < n;i++)cin >> v[i];
    while (right < n) {
        //������
        Sum = Sum + v[right];
        right++;
        //�ж�
        if (Sum > Max)Max = Sum;
        //������
        while (Sum < 0) {
            ++left;
            Sum = Sum - v[left];
        }
    }
    cout << Max;
    return 0;
}
// 64 λ������� printf("%lld")