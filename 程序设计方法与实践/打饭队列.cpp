#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;
    queue<string> queue;

    while(n--)
    {
        string operation;
        cin >> operation;

        if(operation == "Arrive")
        {
            string name;
            cin >> name;
            queue.push(name);
        }
        else if(operation == "Leave")
        {
            if(!queue.empty())  
                queue.pop();
        }
        else if(operation == "QueueHead")
        {
            if(!queue.empty())
                cout << queue.front() << endl;
            else
                cout << "Empty queue" << endl;
        }
        else if(operation == "QueueTail")
        {
            if(!queue.empty())
                cout << queue.back() << endl;
            else
                cout << "Empty queue" << endl;
        }
    }

    return 0;
}