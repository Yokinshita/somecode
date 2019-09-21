#include <iostream>

using namespace std;
template<typename T>
class Stack
{
protected:
	struct Node
	{
		T data;
		Node *next;
	};
	Node* top = nullptr;
public:

	void push(T newdata)
	{
		Node* newnode = new Node;
		newnode->data = newdata;
		newnode->next = top;
		top = newnode;
	}

	T pop()
	{
		T data = top->data;
		Node* below = top->next;
		delete top;
		top = below;
		return data;
	}

	T get_top()
	{
		return top->data;
	}

	bool is_empty()
	{
		return top == nullptr;
	}
};

int st(int n)
{
	if (n <= 0)
	{
		return 1;
	}
	else
	{
		return st(n - 1)*n;
	}
}
int main()
{
	cout << st(3);
}