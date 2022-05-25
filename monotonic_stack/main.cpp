#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<stack>

#pragma region 496. 下一个更大的元素I
// 暴力解法
std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::vector<int> rets;
    for (auto val1 : nums1) {
        auto valIter = std::find(nums2.begin(), nums2.end(), val1);
        int val = *valIter;
        for(; valIter != nums2.end(); valIter++) {
            if (*valIter > val) {
                rets.push_back(*valIter);
                break;
            }
        }
        if (valIter == nums2.end()) {
            rets.push_back(-1);
        }
    }
    return rets;
}

// 单调栈+哈希表
std::vector<int> NextGreaterElement1(std::vector<int>& num1, std::vector<int>& num2)
{
    std::stack<int> sk;
    std::map<int, int> val2NextGreaterVal;
    int num = num2.size();

    // // 从第二元素开始遍历大数组num2
    // 当前元素大于栈顶元素则栈顶元素输出， 若栈不空则继续判断是否大于栈顶；若栈为空或者小于栈顶元素当前元素入栈
    for (int i = 0; i < num; i++) {
        int val = num2[i];
        // TODO 可以优化，这里这样写是为了流程清晰
        int topVal = 0;
        if (!sk.empty()) {
            topVal = sk.top();
        }
        while (!sk.empty() && (val > topVal)) {
            val2NextGreaterVal.emplace(topVal, val);
            sk.pop();
            if (!sk.empty()) {
                topVal = sk.top();
            }
        }
        sk.emplace(val);
    }
    while (!sk.empty()) {
        val2NextGreaterVal.emplace(sk.top(), -1);
        sk.pop();
    }

    std::vector<int> rets;
    for (auto val : num1) {
        auto iter = val2NextGreaterVal.find(val);
        if (iter != val2NextGreaterVal.end()) {
            rets.emplace_back(iter->second);
        }
    }

    return rets;
}
#pragma endregion

int main()
{
    std::vector<int> num1 {4,1,2};
    for (auto val : num1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::vector<int> num2 {1,3,4,2};
    for (auto val : num2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::vector<int> rets = NextGreaterElement1(num1, num2);
    std::cout << "output:" << std::endl;
    for (auto val : rets) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}