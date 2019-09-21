#include<iostream>

template<typename T>
class Queue
{
public:
	Queue()
	{
		front = rear = nullptr;
	}

	bool add(T newdata)
	{
		Node* newnode = new Node;
		newnode->data = newdata;
		newnode->next = nullptr;
		if (front == nullptr)
		{
			front = newnode;
			rear = newnode;
		}
		else
		{
			rear->next = newnode;
			rear = newnode;
		}
		return true;
	}

	T del()
	{
		if (front->next == nullptr)
		{
			throw 1;
		}
		Node* tempnode = front->next;
		T tempdata = front->data;
		delete front;
		front = tempnode;

		return tempdata;
	}

private:
	struct Node {
		T data;
		Node* next;
	};
	Node* front;
	Node* rear;
};
int main()
{
	Queue<int> queue;
	queue.add(5);
	queue.add(3);
	queue.add(4);

	try {
		std::cout << queue.del() << " ";
		std::cout << queue.del() << " ";
		std::cout << queue.del() << " ";
		std::cout << queue.del() << " ";
	}catch (int)
	{
		std::cout << "error!queue is emtpy" << std::endl;
		return 0;
	}

	return 0;
}