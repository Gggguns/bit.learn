#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <unordered_set>
using namespace std;
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        //���ڲ���
        unordered_set<int> hash;
        for (auto e : nums1)hash.insert(e);
        //ȥ��
        unordered_set<int> nums;
        for (auto e : nums2)nums.insert(e);
        //�ó����
        vector<int> ret;
        for (auto e : nums)if (hash.count(e))ret.push_back(e);
        return ret;
    }
};
int main() {
    return 0;
}