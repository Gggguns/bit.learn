#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
class Solution {
public:
    /**
     * �����е����������������������Ѿ�ָ���������޸ģ�ֱ�ӷ��ط����涨��ֵ����
     *
     *
     * @param head ListNode�� the head
     * @return bool������
     */
    bool isPail(ListNode* head) {
        if (!head)return true;

        vector<size_t> v1, v2;
        ListNode* cur = head;
        while (cur)
        {
            v1.push_back(cur->val);
            v2.push_back(cur->val);
            cur = cur->next;
        }
        reverse(v1.begin(), v1.end());
        int i = 0;
        for (i = 0;i < v1.size();i++)
        {
            if (v1[i] != v2[i])
                return false;
        }
        return true;
    }
};