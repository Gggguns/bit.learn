#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    void sortColors(vector<int>& nums) {
        //����������
        int left = -1, cur = 0, right = nums.size();
        while (cur < right) {
            //��ɫ
            if (nums[cur] == 0) {
                left++;
                swap(nums[cur], nums[left]);
                if (cur == left)cur++;
            }
            //��ɫ
            else if (nums[cur] == 1)cur++;
            //��ɫ
            else {
                right--;
                swap(nums[cur], nums[right]);
            }
        }
    }
};
int main() {
	return 0;
}
