#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
    //��ȡ��������
    int n = 0;
    cin >> n;
    //��ȡ���в�����Ա��ˮƽֵ
    vector<int> v;
    int i = 0;
    int account = 3 * n;
    int a_i = 0;
    for (i = 0;i < account;i++)
    {
        cin >> a_i;
        v.push_back(a_i);
    }
    //������ˮƽֵ��������
    sort(v.begin(), v.end());
    //�������ֵ
    long count = 0;
    for (int i = 1;i <= n;i++)
    {

        count += v[account - 2 * i];
    }
    cout << count;
}