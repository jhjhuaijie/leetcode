#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<unordered_set>
#pragma region 219. 存在重复元素 II
#pragma region 暴力解法
bool ContainsNearbyDuplicate(std::vector<int>& nums, int k)
{
    int cnt = nums.size();
    bool ret = false;
    for (int i = 0; i < cnt; i++) {
        int maxIndex = 0;
        if ((i + k) < cnt) {
            // 未超出数组可查询的最大索引
            maxIndex = i + k;
        } else {
            // 超出数组可查询的最大索引
            maxIndex = cnt - 1;
        }
        // 判断子数组中是否有值相同的
        for (int j = i; j <= maxIndex; j++) {
            for (int t = j + 1; t <= maxIndex; t++) {
                if (nums[j] == nums[t]) {
                    ret = true;
                }
            }
        }
    }
    return ret;
}
#pragma endregion

#pragma region 滑动窗口
bool ContainsNearbyDuplicateBySlidingWindow(std::vector<int>& nums, int k)
{
    std::unordered_set<int> sets;
    for (int i = 0; i < nums.size(); i++) {
        // 滑动窗口超多最大数量，窗口向后滑动即删除第一个元素
        if (sets.size() > k) {
            sets.erase(nums[i-k-1]);
        }
        if (sets.count(nums[i])) {
            return true;
        }
        sets.insert(nums[i]);
    }
    return false;
}
#pragma endregion
#pragma endregion
int main()
{
    std::vector<int> nums {1,2,3,1,2,3};
    int k = 2;
    std::cout << ContainsNearbyDuplicateBySlidingWindow(nums, k) << std::endl;
    return 0;
}