#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int mid = 0;
        while (left <= right) {
            mid = left + (right - left) / 2;
            if (nums[mid] > target)right = mid - 1;
            else if (nums[mid] == target)break;
            else left = mid + 1;
        }
        if (nums[mid] == target)return mid;
        else return -1;
    }
};
int main()
{
	return 0;
}