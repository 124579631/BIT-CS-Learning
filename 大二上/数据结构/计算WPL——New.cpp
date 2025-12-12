#include <iostream>
#include <vector>
#include <queue>
#include <functional>

int main()
{
    int n;
    std::cin >> n;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    for(int i = 0; i < n; i++)
    {
        int weight;
        std::cin >> weight;
        pq.push(weight);
    }

    int WPL = 0;
    while(pq.size() > 1)
    {
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();
        int newWeight = first + second;
        WPL += newWeight;
        pq.push(newWeight);
    }

    std::cout << "WPL=" << WPL << std::endl;

    return 0;
}