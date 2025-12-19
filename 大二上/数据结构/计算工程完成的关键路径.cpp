#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>
#include <cstdio> // 用于 scanf, fgets

using namespace std;

// 边结构体
struct Edge {
    int to;
    int weight;
    // 重载小于号，确保 DFS 时优先访问编号小的节点
    bool operator<(const Edge& other) const {
        return to < other.to;
    }
};

// 全局变量
int n, m;
vector<string> nodeNames;
vector<vector<Edge>> adj;
vector<int> inDegree;
vector<int> ve, vl;       // 最早开始时间，最晚开始时间
vector<int> topoOrder;    // 存储拓扑序列
vector<int> pathStack;    // 用于 DFS 存储当前路径

// 解析输入的辅助函数
void parseInput() {
    // 1. 读取节点数和边数
    if (scanf("%d,%d", &n, &m) != 2) return;
    
    // 消耗换行符
    char buffer[1024];
    getchar(); 
    
    // 2. 读取节点名称
    if (!fgets(buffer, 1024, stdin)) return;
    string line = buffer;
    // 将逗号替换为空格方便解析
    for(char &c : line) {
        if(c == ',' || c == '\n' || c == '\r') c = ' ';
    }
    stringstream ss(line);
    string name;
    while(ss >> name) {
        nodeNames.push_back(name);
    }

    // 3. 读取边信息
    adj.resize(n);
    inDegree.assign(n, 0);
    
    if(fgets(buffer, 1024, stdin) == NULL) return;
    string edgeLine = buffer;
    
    int u, v, w;
    const char* ptr = edgeLine.c_str();
    while(*ptr) {
        // 寻找 '<' 开始解析
        if(*ptr == '<') {
            if(sscanf(ptr, "<%d,%d,%d>", &u, &v, &w) == 3) {
                adj[u].push_back({v, w});
                inDegree[v]++;
            }
        }
        ptr++;
    }

    // 对邻接表中的边进行排序，保证输出顺序（题目要求从小到大）
    for(int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
}

// 深度优先搜索打印关键路径
// 逻辑：沿着满足 ve[u] + w == vl[v] 的边走，直到无路可走
void dfs(int u) {
    pathStack.push_back(u);

    bool isEnd = true; // 标记当前节点是否是路径终点
    for (auto& edge : adj[u]) {
        int v = edge.to;
        int w = edge.weight;
        // 关键活动判断条件：最早开始时间 + 持续时间 == 下个节点的最晚开始时间
        if (ve[u] + w == vl[v]) {
            isEnd = false; 
            dfs(v);
        }
    }

    // 如果没有后续的关键活动，说明到达了关键路径的终点
    if (isEnd) {
        // 输出路径
        for (size_t i = 0; i < pathStack.size(); i++) {
            cout << nodeNames[pathStack[i]];
            if (i != pathStack.size() - 1) cout << "-";
        }
        cout << endl;
    }

    pathStack.pop_back(); // 回溯
}

int main() {
    parseInput();

    // --- 步骤 1: 拓扑排序 (Kahn算法) ---
    // 使用最小堆优先队列，保证同入度节点按编号从小到大处理
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for(int i = 0; i < n; i++) {
        if(inDegree[i] == 0) {
            pq.push(i);
        }
    }

    ve.assign(n, 0); // 初始化 ve

    while(!pq.empty()) {
        int u = pq.top();
        pq.pop();
        topoOrder.push_back(u);

        for(auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            // 计算最早开始时间 ve
            if(ve[u] + w > ve[v]) {
                ve[v] = ve[u] + w;
            }
            inDegree[v]--;
            if(inDegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    // 检测是否有环
    // 注意：将 size() 强转为 int 避免警告，或者比较 size_t
    if(topoOrder.size() < (size_t)n) {
        cout << "NO TOPOLOGICAL PATH" << endl;
        return 0;
    }

    // 输出拓扑排序结果
    for(size_t i = 0; i < topoOrder.size(); i++) {
        cout << nodeNames[topoOrder[i]];
        if(i != topoOrder.size() - 1) cout << "-";
    }
    cout << endl;

    // --- 步骤 2: 计算最晚开始时间 vl ---
    
    // 找到工程总耗时（所有节点中 ve 的最大值）
    int maxTime = 0;
    for(int i = 0; i < n; i++) {
        if(ve[i] > maxTime) {
            maxTime = ve[i];
        }
    }
    
    // 初始化 vl 为最大时间
    vl.assign(n, maxTime);

    // 逆拓扑序计算 vl
    for(int i = n - 1; i >= 0; i--) {
        int u = topoOrder[i];
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            // vl[u] = min(vl[v] - w)
            if (vl[v] - w < vl[u]) {
                vl[u] = vl[v] - w;
            }
        }
    }
    
    // --- 步骤 3: 输出所有关键路径 ---
    // 关键路径一定从源点开始（ve == 0 且 vl == 0 的点）
    // 并且按照题目要求的节点编号从小到大遍历
    for(int i = 0; i < n; i++) {
        if (ve[i] == 0 && vl[i] == 0) {
            dfs(i);
        }
    }

    return 0;
}