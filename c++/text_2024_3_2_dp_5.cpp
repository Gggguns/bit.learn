#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int uniquePaths(int m, int n) {
        //创建dp表·
        //初始化
        //填表
        //返回值
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1;i < m;i++)
            for (int j = 1;j < n;j++)
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        return dp[m - 1][n - 1];
    }
};
int main()
{
    int m = 0, n = 0;
    cin >> m >> n;
    Solution s;
    cout << s.uniquePaths(m, n);
	return 0;
}