#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<vector>
using namespace std;

int main() {
    int V = 0, n = 0;
    cin >> V >> n;
    vector<int> volumes(n);
    //��¼n����Ʒ�����
    for (int i = 0;i < n;i++)cin >> volumes[i];
    //ȷ��ʹ����������ֵ
    vector<vector<int>> dp(n, vector<int>(V + 1));
    //��ʼ��
    for (int i = volumes[0];i <= V;i++)dp[0][i] = volumes[0];
    //���
    for (int i = 1;i < n;i++) {
        //��ǰ��Ʒ�����
        int cur = volumes[i];
        for (int j = 0;j <= V;j++) {
            if (j - cur >= 0)dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - cur] + cur);
            else dp[i][j] = dp[i - 1][j];
        }
    }
    //����ʣ���������Сֵ
    int Res = V - dp[n - 1][V];
    cout << Res;
    return 0;
}