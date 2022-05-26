#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<stack>
#include<deque>

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

#pragma region 下一个更大元素 II 循环数组
// 解析：循环遍历数组入栈，入栈时判断当前元素是否大于栈顶元素？若大于栈顶元素则找到了栈顶元素
// 的下一个更大元素，栈顶元素出栈，若栈顶元素不空继续判断当前元素是否大于栈顶元素直到栈顶元素
// 大于当前元素，当前元素入栈；遍历完数组后，栈内的元素都是从大到小排列（栈底->栈顶），栈底元素
// 是栈内所有其它元素的下一个最大元素
// 单调栈+双端队列（模拟单调栈）
std::vector<int> NextGreaterElement2(std::vector<int>& num2)
{
    std::deque<int> dq;
    std::map<int, int> val2NextGreaterVal;
    int num = num2.size();

    // // 从第二元素开始遍历大数组num2
    // 当前元素大于栈顶元素则栈顶元素输出， 若栈不空则继续判断是否大于栈顶；若栈为空或者小于栈顶元素当前元素入栈
    for (int i = 0; i < num; i++) {
        int val = num2[i];
        // TODO 可以优化，这里这样写是为了流程清晰
        int topVal = 0;
        if (!dq.empty()) {
            // 取栈顶元素
            topVal = dq.back();
        }
        while (!dq.empty() && (val > topVal)) {
            val2NextGreaterVal.emplace(topVal, val);
            dq.pop_back();
            if (!dq.empty()) {
                topVal = dq.back();
            }
        }
        dq.push_back(val);
    }
    // 栈底元素
    int bottomVal = dq.front();
    dq.pop_front();
    // 栈底元素为整个数组中最大的元素（存在问题：重复的最大元素）
    val2NextGreaterVal.emplace(bottomVal, -1);
    while (!dq.empty()) {
        val2NextGreaterVal.emplace(dq.back(), bottomVal);
        dq.pop_back();
    }

    std::vector<int> rets;
    for (auto val : num2) {
        auto iter = val2NextGreaterVal.find(val);
        if (iter != val2NextGreaterVal.end()) {
            rets.emplace_back(iter->second);
        }
    }

    return rets;
}
#pragma endregion


#pragma region 739.每日温度 stack<pair<int,int>>
std::vector<int> DailyTemperatures(std::vector<int>& temperatures) {
    // 栈存储位置和值得映射
    std::stack<std::pair<int, int>> sk;
    std::map<int, int> tempt2NextGreaterDistance;
    int num = temperatures.size();
    for (int i = 0; i < num; i++) {
        // 当前温度到下一个更大温度的距离
        int distance = 0;
        while (!sk.empty() && (sk.top().second < temperatures[i])) {
            tempt2NextGreaterDistance.emplace(std::make_pair(sk.top().first, i - sk.top().first));
            sk.pop();
        }
        sk.emplace(std::make_pair(i, temperatures[i]));
    }
    while (!sk.empty()) {
        tempt2NextGreaterDistance.emplace(std::make_pair(sk.top().first, 0));
        sk.pop();
    }

    std::vector<int> rets;
    for (auto item : tempt2NextGreaterDistance) {
        rets.emplace_back(item.second);
    }
    return rets;
}
// 优化，栈中存储元素的位置
std::vector<int> DailyTemperatures2(std::vector<int>& temperatures) {
    std::stack<int> sk;
    int num = temperatures.size();
    std::vector<int> rets(num);
    for (int i = 0; i < num; i++) {
        while (!sk.empty() && (temperatures[sk.top()] < temperatures[i])) {
            rets[sk.top()] = i - sk.top();
            sk.pop();
        }
        sk.emplace(i);
    }
    return rets;
}
#pragma endregion
int main()
{
    std::vector<int> tempratures {73,74,75,71,69,72,76,73};
    for (auto val : tempratures) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::vector<int> rets = DailyTemperatures(tempratures);
    std::cout << "output:" << std::endl;
    for (auto val : rets) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}