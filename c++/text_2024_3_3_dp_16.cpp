#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        //����dp��
        //��ʼ��
        //���
        //����ֵ
        int n = prices.size();
        if (n < 2)return 0;
        vector<vector<int>> dp(n, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1;i < n;i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
            dp[i][1] = max(dp[i - 1][0] + prices[i] - fee, dp[i - 1][1]);
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};
int main()
{
	return 0;
}