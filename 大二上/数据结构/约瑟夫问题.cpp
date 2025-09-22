#include <iostream>

using namespace std;

struct Node
{
	int id;
	Node * next;	
};

Node* createList(int n)
{
	Node *head = NULL;	
	Node *cur = NULL;	
	Node *pre = NULL;
	
	for(int i = 1; i <= n; i++)
	{
		cur = new Node;
		cur->id = i;
		if(!head)
			head = cur;
		else
			pre->next = cur;
		pre = cur;
	}
	cur->next = head;
	
	return head;
};

Node *head;

void game(int n, int k, int m)
{
	Node *cur = head;
	Node *pre = NULL;
	
	for(int i = 1; i < k; i++)//从k开始
	{
		pre = cur;
		cur = cur->next;
	}
	
	int count = 0;
	while(n--)
	{
		for(int i = 1; i < m; i++)
		{
			pre = cur;
			cur = cur->next;
		}
		cout << cur->id;
		count++;
		
		if(n)
		{
			if(count % 10 != 0)
				cout << " ";
			else
				cout << "\n";
		}
		else
		{
			cout << "\n";
		}
		
		Node *temp = cur;
		pre->next = cur->next;
		cur = cur->next;
		delete temp;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, k, m;
	char c;
	cin >> n >> c >> k >> c >> m;
	
	if(n < 1 || k < 1 || m < 1)
	{
		cout << "n,m,k must bigger than 0." << endl;
		return 0;
	}
	else if(k > n)
	{
		cout << "k should not bigger than n." << endl;
		return 0;
	}
	head = createList(n);
	game(n, k, m);
	
	return 0;
}