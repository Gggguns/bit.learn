#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int n = 0;
    cin >> n;
    vector<long long> cost(n);
    vector<long long> res(n + 1);
    //����
    for (auto& e : cost)cin >> e;
    //����
    for (int i = 2;i <= n;i++) {
        res[i] = min(res[i - 1] + cost[i - 1], res[i - 2] + cost[i - 2]);
    }
    cout << res[n];
    return 0;
}
// 64 λ������� printf("%lld")