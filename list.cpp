#include <iostream>
#include <vector>
using namespace std;

template<typename T = int>
class Table
{
public:
	void create_table()
	{
		int col, row;
		HeadNode *head = new HeadNode;
		head->next = nullptr;
		std::cout << "请输入表的行数与列数:" << std::endl;
		std::cin >> col >> row;
		head->col = col;
		head->row = row;
		begin = head;

		for (int i = 0; i < head->row; i++)
		{
			std::cout << "依次输入第" << i + 1 << "列的数据:" << std::endl;
			MIddleNode *newnode = new MIddleNode;
			for (int j = 0; j < head->row; j++)
			{
				int newdata;
				std::cin >> newdata;
				newnode->data.push_back(newdata);
			}
			if (head->next == nullptr)
			{
				head->next = newnode;
				newnode->next = nullptr;
				last = newnode;
			}
			else
			{
				last->next = newnode;
				last = newnode;
			}
			newnode->next = nullptr;
		}
	}
	bool destory_table()
	{
		MIddleNode *forward, *back;
		back = begin->next;
		forward = begin->next;
		while (forward != nullptr)
		{
			delete back;
			back = forward;
			forward = forward->next;
		}
		delete begin;
		begin = nullptr;
	}
	void display_table()
	{
		MIddleNode *temp = begin->next;
		int CurrentRow = 1;
		while (temp != nullptr)
		{
			std::cout << "输出第" << CurrentRow << "列的数据:" << std::endl;
			for (int k = 0; k < begin->row; k++)
			{
				std::cout << temp->data.at(k) << " ";
			}
			temp = temp->next;
			std::cout << std::endl;
		}
		CurrentRow += 1;
	}
private:
	struct MIddleNode
	{
		T data;
		MIddleNode *next;
	};
	struct HeadNode {
		int col;
		int row;
		MIddleNode *next;
	};
	HeadNode *begin = nullptr;
	MIddleNode *last = nullptr;
};

template<typename T>
class Orderlist
{
	//begin指向第一个节点
	//链表的末尾节点没有值，且其next指向空指针
	//last指向末尾节点
protected:
	struct Node {
		T data;
		Node *next;
	};
	Node *begin;
	Node *last;
	int size;

public:
	Orderlist()
	{
		begin = new Node;
		begin->next = nullptr;
		last = begin;
		size = 0;
	}

	bool delete_list()
	{
		Node* temp = begin->next;
		while (temp->next != nullptr)
		{
			delete begin;
			begin = temp;
			temp = temp->next;
		}
		delete temp;

		return true;
	}

	bool add_data(T NewData)
	{
		last->data = NewData;
		last->next = new Node;
		last->next->next = nullptr;
		last->next->data = NULL;
		last = last->next;
		size++;

		return true;
	}

	bool isempty()
	{
		return begin->next == nullptr;
	}

	bool display_data()
	{
		int i = 1;
		Node* temp = begin;
		if (this->isempty())
		{
			cout << "链表为空" << endl;
			return true;
		}
		while (temp->next != nullptr)
		{
			cout << "第" << i << "个元素为" << temp->data << endl;
			temp = temp->next;
			i++;
		}
		return true;
	}

	T getdata_by_index(int i)
	{
		if (i > size)
		{
			cout << "超出链表最大长度" << endl;
			return begin->data;
		}
		int j = 1;
		Node *temp = begin;
		while (j != i)
		{
			temp = temp->next;
			j++;
		}
		return temp->data;
	}

	int getindex_by_value(T value)
	{
		int j = 1;
		Node* temp = begin;
		while (temp->data != value && temp->next != nullptr)
			//若不添加&& temp->next != nullptr条件且未查找到需要的值时
			//当temp平移至最后一个指针时，temp->data是未定义的，不会有返回值
		{
			temp = temp->next;
			j++;
		}
		if (temp->next == nullptr)
		{
			cout << "该值在链表中不存在" << endl;
			return 0;
		}
		else
		{
			return j;
		}
	}

	void insert_data(T newdata)
	{
		Node* pre = begin;

		while (pre->next != nullptr&&pre->next->data < newdata)
		{
			pre = pre->next;
		}
		Node* temp = new Node;
		temp->data = newdata;
		temp->next = pre->next;
		pre->next = temp;

	//	//一种解决方法
	//	if (begin->next == nullptr)
	//	{
	//		if (newdata < begin->data)
	//		{
	//			Node* newnode = new Node;
	//			newnode->data = newdata;
	//			newnode->next = begin;
	//			begin = newnode;
	//		}
	//		else
	//		{
	//			Node* newnode = new Node;
	//			newnode->data = newdata;
	//			newnode->next = nullptr;
	//			begin->next = newnode;
	//		}
	//	}
	//	else
	//	{
	//		Node* pre = begin;

	//		while (pre != nullptr&&pre->next->data < newdata)
	//		{
	//			pre = pre->next;
	//		}
	//		Node* temp = new Node;
	//		temp->data = newdata;
	//		temp->next = pre->next;
	//		pre->next = temp;
	//	}
	}

	bool delete_data(int position)
	{
		int j = 1;
		Node*temp = begin;
		while (j != position - 1 && temp->next->next != nullptr)
			//j != position-1使得temp指向第position个节点前的一个节点
		{
			temp = temp->next;
			j++;
		}
		if (temp->next->next == nullptr)
		{
			cout << "给出的删除位置超出链表长度" << endl;
			return true;
		}
		else
		{
			Node *currentpointer = temp->next;
			temp->next = temp->next->next;
			delete currentpointer;

			//错误的实现，原意是希望事先利用currentpointer存储temp的地址，
			//然后再将后一个节点连接到前一个节点上，
			//但此时currentpointer也被同步改变，
			//所以delete currentpointer->next会导致野指针
			//Node *currentpointer = temp;
			//temp->next=temp->next->next;
			//delete currentpointer->next;
		}
		return true;
	}
};


int main()
{
	/*Table<int> a;
	a.create_table();
	a.display_table();
	std::cout << __cplusplus;*/
	Orderlist<int> a;
	a.add_data(1);
	a.display_data();
	a.insert_data(5);
	a.display_data();
	a.insert_data(4);
	a.display_data();
	a.insert_data(3);
	a.display_data();

	return 0;
}