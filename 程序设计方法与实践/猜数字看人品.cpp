#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

bool comp(int guess, int res[][2], int i);

int main()
{
    int guess = -1;
    int i = 0;
    bool lie = false;
    string gets;
    string high = "too high";
    string low = "too low";
    string right = "right on";
    int res[20][2] = {0};

    while(1)
    {
        cin >> guess;
        if (guess == 0) break;
        cin.ignore();
        getline(cin,gets);

        if (gets == high)
		{
            res[i][0] = guess;
            res[i][1] = -1;
            i++;
        }
        else if (gets == low)
		{
            res[i][0] = guess;
            res[i][1] = 1;
            i++;
        }
        else if (gets == right)
		{
            lie = comp(guess,res,i);
            if (!lie)
                cout << "Tom may be honest" << endl;
            else
                cout << "Tom is dishonest" << endl;
            i = 0;
        }
        else
		{
            cout << "Error" << endl;
        }
    }
}

bool comp(int guess, int res[][2], int i)
{
    for (int j = 0; j < i; j++)
    {
        if (res[j][1] == 1)  // too low
        {
            if (guess <= res[j][0])
				return true;
        }
        else if (res[j][1] == -1) // too high
        {
            if (guess >= res[j][0])
				return true;
        }
    }
    return false;
}
/*
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int guess;
    string response;
    int low = 1, high = 10; // 初始范围

    while (true) {
        cin >> guess;
        if (guess == 0) break; // 输入结束
        cin.ignore();
        getline(cin, response);

        if (response == "too low") 
		{
            low = max(low, guess + 1);
        }
        else if (response == "too high") 
		{
            high = min(high, guess - 1);
        }
        else if (response == "right on") 
		{
            if (guess >= low && guess <= high)
                cout << "Tom may be honest" << endl;
            else
                cout << "Tom is dishonest" << endl;
            // 重置范围
            low = 1;
            high = 10;
        }
    }
    return 0;
}
*/