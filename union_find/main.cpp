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

#pragma region 并查集
// 初始化并查集 节点的父节点是其本身
void Init(std::vector<int>& parent)
{
    int num = parent.size();
    for (int i = 0; i < num; i++) {
        parent[i] = i;
    }
}

// 查找集合的根节点，根节点的父节点是其本身，作为一个集合的标志
int Find(std::vector<int>& parent, int index)
{
    if (parent.empty() || !(index < parent.size())) {
        std::cout << "error" << std::endl;
        return 0;
    }
    // 压缩路径
    if (parent[index] != index) {
        parent[index] = Find(parent, parent[index]);
    }
    return parent[index];
}

// 合并两个集合，找到根节点
void Union(std::vector<int>& parent, int index1, int index2)
{
    parent[Find(parent, index1)] = Find(parent, index2);
}

int FindCircleNumByUnionFind(std::vector<std::vector<int>>& isConnected)
{
    int num = isConnected.size();
    std::vector<int> parent(num);
    Init(parent);
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (i == j) {
                continue;
            }
            if (isConnected[i][j] == 1) {
                Union(parent, i, j);
            }
        }
    }

    int provinces = 0;
    for (int i = 0; i < num; i++) {
        if (parent[i] == i) {
            provinces++;
        }
    }

    return provinces;
}
#pragma endregion
#pragma endregion

#pragma region 684. 冗余连接
std::vector<int> FindRedundantConnection(std::vector<std::vector<int>>& edges)
{
    std::vector<int> ret(2);
    int num = edges.size();
    std::vector<int> parent(num);
    for (int i = 0; i < num; i++) {
        parent[i] = i;
    }
    for (auto& edge : edges) {
        int index1 = edge[0] - 1;
        int index2 = edge[1] - 1;
        // 判断两个节点是否属于同一个集合
        if (Find(parent, index1) == Find(parent, index2)) {
            ret[0] = edge[0];
            ret[1] = edge[1];
            continue;
        }
        Union(parent, index1, index2);
    }

    return ret;
}
#pragma endregion
int main()
{
    std::vector<std::vector<int>> edges {
        {1, 2},
        {2, 3},
        {3, 4},
        {1, 4},
        {1, 5}
    };
    std::vector<int> ret = FindRedundantConnection(edges);
    for (const auto& val : ret) {
        std::cout << val << std::endl;
    }
    return 0;
}