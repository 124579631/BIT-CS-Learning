#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    while (std::cin >> n && n != 0) {
        // 使用 long long 防止高度和最终面积溢出 int 范围
        // 多申请一个空间用于在末尾放置高度为 0 的哨兵
        std::vector<long long> h(n + 1);
        
        for (int i = 0; i < n; ++i) {
            std::cin >> h[i];
        }
        // 末尾哨兵：高度为 0，确保栈内剩余元素最后都能被弹出计算
        h[n] = 0;

        std::stack<int> st; // 单调递增栈，存储的是下标
        long long maxArea = 0;

        for (int i = 0; i <= n; ++i) {
            // 当当前木板高度小于栈顶木板高度时，说明栈顶木板向右无法延伸了
            // 此时弹出栈顶，计算以该栈顶木板高度为矩形高度的最大面积
            while (!st.empty() && h[st.top()] > h[i]) {
                long long height = h[st.top()];
                st.pop();

                // 计算宽度：
                // 如果栈为空，说明 height 是之前所有木板中最小的，宽度为 [0, i-1]，长度为 i
                // 如果栈不为空，左边界是新的栈顶元素（st.top()），右边界是 i，宽度为 (i - st.top() - 1)
                int width = st.empty() ? i : (i - st.top() - 1);
                
                maxArea = std::max(maxArea, height * width);
            }
            st.push(i);
        }

        std::cout << maxArea << std::endl;
    }

    return 0;
}