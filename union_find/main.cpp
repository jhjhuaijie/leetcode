#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#pragma region 547. 省份数量
#pragma region 深度遍历
void Dfs(std::vector<std::vector<int>>& isConnected, std::vector<bool>& visited, int curPos)
{
    for (int nextPos = 0; nextPos < isConnected.size(); nextPos++) {
        if ((isConnected[curPos][nextPos] == 1 && (!visited[nextPos]))) {
            visited[nextPos] = true;
            Dfs(isConnected, visited, nextPos);
        }
    }
}

int FindCircleNum(std::vector<std::vector<int>>& isConnected)
{
    int num = isConnected.size();
    std::vector<bool> visited(num);
    int cnt = 0;
    for (int i = 0; i < num; i++) {
        if (!visited[i]) {
            Dfs(isConnected, visited, i);
            cnt++;
        }
    }
    return cnt;
}
#pragma endregion

#pragma region 广度遍历
int FindCircleNumByBfs(std::vector<std::vector<int>>& isConnected)
{
    int cnt = 0;
    int num = isConnected.size();
    std::queue<int> qe;
    std::vector<bool> visited(num, false);
    
    for (int pos = 0; pos < num; pos++) {
        if (visited[pos]) {
           continue;
        }
        visited[pos] = true;
        qe.push(pos);
        while (!qe.empty()) {
            int curPos = qe.front();
            qe.pop();
            for (int nextPos = 0; nextPos < num; nextPos++) {
                if ((isConnected[curPos][nextPos] == 1) && (!visited[nextPos])) {
                    qe.push(nextPos);
                    visited[nextPos] = true;
                }
            }
        }
        cnt++;
    }
    return cnt;
}
#pragma endregion


#pragma endregion
int main()
{
    std::vector<std::vector<int>> isconnected {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    std::cout << "province: ";
    std::cout << FindCircleNumByBfs(isconnected) << std::endl;
    return 0;
}