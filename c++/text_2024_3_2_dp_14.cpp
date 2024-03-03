#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        //创建dp表
        //初始化
        //填表
        //返回值
        int n = costs.size();
        vector<vector<int>> dp(n, vector<int>(3));
        dp[0][0] = costs[0][0];
        dp[0][1] = costs[0][1];
        dp[0][2] = costs[0][2];
        for (int i = 1;i < n;i++)
        {
            dp[i][0] = min(dp[i - 1][1], dp[i - 1][2]) + costs[i][0];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]) + costs[i][1];
            dp[i][2] = min(dp[i - 1][1], dp[i - 1][0]) + costs[i][2];
        }
        return min(min(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]);
    }
};
int main()
{
	return 0;
}