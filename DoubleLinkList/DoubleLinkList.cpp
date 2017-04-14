// DoubleLinkList.cpp : 定义控制台应用程序的入口点。
#include"iostream"
using namespace std;
typedef int DataType;
class LinkList;
class Node
{
	friend LinkList;
	friend ostream &operator<<(ostream&os, Node&n);
	friend ostream &operator<<(ostream&os, LinkList&list);
public:
	Node(DataType x) :_data(x), _next(NULL), _front(NULL)
	{}
private:
	DataType _data;
	Node*_next;
	Node*_front;
};
ostream &operator<<(ostream&os, Node&n)
{
	os << n._data;
	return os;
}
class LinkList
{
	friend ostream& operator<<(ostream &os, LinkList &list);
private:
	Node*_head;
	Node*_tail;
public:
	LinkList() :_head(NULL), _tail(NULL)
	{}
	LinkList(const LinkList&list) :_head(NULL), _tail(NULL)
	{
		Node*cur = list._head;
		while (cur)
		{
			Node*tmp = new Node(cur->_data);
			if (_tail)
			{
				_tail->_next = tmp;
				tmp->_front = _tail;
				_tail = tmp;
			}
			else
			{
				_head = tmp;
				_tail = tmp;
			}
			cur = cur->_next;
		}
	}
	~LinkList()
	{
		Node*cur = _head;
		while (cur)
		{
			Node*del = cur;
			cur = cur->_next;
			delete del;
			del = NULL;
		}
	}
public:
	void PushBack(DataType x)
	{
		Node*NewNode = new Node(x);
		if (_tail)
		{
			_tail->_next = NewNode;
			NewNode->_front = _tail;
			_tail = NewNode;
		}
		else
		{
			_head = NewNode;
			_tail = NewNode;
		}
	}
	void PopBack()
	{
		if (!_head&&!_tail)
		{
			//空链表
			cout << "链表空，不可尾删除！" << endl;
			return;
		}
		else if (_head == _tail)
		{
			//只有一个节点
			delete _tail;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			//俩节点以上
			Node*tmp = _tail;
			_tail = tmp->_front;
			_tail->_next = NULL;
			delete tmp;
			tmp = NULL;
		}
	}
	void PushFront(DataType x)
	{
		Node*NewNode = new Node(x);
		if (_head)
		{
			Node*tmp = _head;
			NewNode->_next = tmp;
			tmp->_front = NewNode;
		}
		else
		{
			_tail = NewNode;
		}
		_head = NewNode;//头指针
	}
	void PopFront()
	{
		if (!_head&&!_tail)
		{
			//空
			cout << "链表为空，不可头删！" << endl;
			return;
		}
		else if (_head == _tail)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			//俩点以上
			Node*del = _head;
			_head = del->_next;
			_head->_front = NULL;
			delete del;
			del = NULL;
		}
	}
	Node*FindNum(DataType x)
	{
		Node*cur = _head;
		while (cur)
		{
			if (cur->_data == x)
			{
				return cur;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return NULL;
	}
	void Insert(Node*pos, DataType x)
	{
		//在指定位置后插入元素
		Node*NewNode = new Node(x);
		if (pos->_next)
		{
			NewNode->_front = pos;
			pos->_front->_next = NewNode;
			NewNode->_front = pos->_front;
			pos->_front = NewNode;
		}
		else
		{
			//在第一个结点前插入
			NewNode->_next = pos;
			pos->_front = NewNode;
			_head = NewNode;
		}
	}
	void Insert(int, Node*pos, DataType x)
	{
		//在指定位置后插入
		Node*NewNode = new Node(x);
		if (pos->_front)
		{
			NewNode->_next = pos;
			pos->_front->_next = NewNode;
			NewNode->_front = pos->_front;
			pos->_front = NewNode;
		}
		else
		{
			NewNode->_next = pos;
			pos->_front = NewNode;
			_head = NewNode;//更新头
		}
	}
	void Remove(DataType &x)
	{
		Node*pos = this->FindNum(x);
		if (pos != NULL)
		{
			if ((!(pos->_front)) && (pos->_next))
			{
				//删除第一个结点
				Node*tmp = pos->_next;
				tmp->_front = NULL;
				_head = tmp;
			}
			else
			{
				//删除点在链表中间
				Node*front = pos->_front;
				Node*next = pos->_next;
				next->_front = front;
				front->_next = next;
			}
			delete pos;
			pos = NULL;
		}
	}
	void RemoveAll(DataType&x)
	{
		Node*cur = _head;
		Node*ret = this->FindNum(x);
		if (ret != _head)
		{
			while (cur)
			{
				Remove(x);
				cur = cur->_next;
			}
		}
	}
	void Sort()
	{
		int flag = 1;
		Node*cur = _head;
		Node*tail = NULL;
		while (cur != tail)
		{
			while (cur->_next != tail)
			{
				if (cur->_data > cur->_next->_data)
				{
					DataType tmp = cur->_data;
					cur->_data = cur->_next->_data;
					cur->_next->_data = tmp;
					flag = 0;
				}
				cur = cur->_next;
			}
			if (flag == 1)
				break;
			tail = cur;
			cur = _head;
		}
	}
	void Erase(Node*pos)
	{
		if ((!(pos->_front)) && (pos->_next))
		{
			//删除第一个节点
			Node*tmp = pos->_next;
			tmp->_front = NULL;
			_head = tmp;
		}
		else if (pos->_front && (!(pos->_next)))
		{
			//删除最后一个节点
			Node*tmp = pos->_front;
			tmp->_next = NULL;
			_tail = tmp;
		}
		else
		{
			//删除中间节点
			Node*front = pos->_front;
			Node*next = pos->_next;
			next->_front = front;
			front->_next = next;
		}
		delete pos;
		pos = NULL;
	}
};
ostream& operator<<(ostream &os, LinkList&list)
{
	Node*cur = list._head;
	while (cur)
	{
		os << (*cur) << " ";
		cur = cur->_next;
	}
	return os;
}
void menu()
{
	cout << "************1.尾插************2.尾删**************" << endl;
	cout << "************3.头插************4.头删**************" << endl;
	cout << "************5.指定位置后插****6.指定位置前插******" << endl;
	cout << "************7.删除指定元素****8.删除所有指定元素**" << endl;
	cout << "************9.排序************0.退出*************" << endl;
	cout << "************11.Erase**********0.退出*************" << endl;
}
void test()
{
	LinkList list;
	Node*ret = NULL;
	int input = 1;
	DataType x, num;
	while (input)
	{
		menu();
		cout << "输入选项：";
		cin >> input;
		switch (input)
		{
		case 1:
			cout << "请输入要插入的数据：";
			cin >> x;
			list.PushBack(x);
			break;
		case 2:
			list.PopBack();
			break;
		case 3:
			cout << "请输入您要插入的数据>";
			cin >> x;
			list.PushFront(x);
			break;
		case 4:
			list.PopFront();
			break;
		case 5:
			cout << "请输入您要查找的数据>";
			cin >> x;
			ret = list.FindNum(x);
			if (ret != NULL)
			{
				cout << "请输入您要插入的数据>";
				cin >> num;
				list.Insert(ret, num);
			}
			else
			{
				cout << "您所查找的数据不存在" << endl;
			}
			break;
		case 6:
			cout << "请输入您要查找的数据>";
			cin >> x;
			ret = list.FindNum(x);
			if (ret != NULL)
			{
				cout << "请输入您要插入的数据>";
				cin >> num;
				list.Insert(0, ret, num);  //0用于占位，构成重载  
			}
			else
			{
				cout << "您所查找的数据不存在" << endl;
			}
			break;
		case 7:
			cout << "请输入您要删除的数据>";
			cin >> x;
			list.Remove(x);
			break;
		case 8:
			cout << "请输入您要删除的数据>";
			cin >> x;
			list.RemoveAll(x);
			break;
		case 9:
			list.Sort();
			break;
		case 10:
			cout << list << endl;
			break;
		case 11:
			cout << "请输入您要擦除的数据>";
			cin >> x;
			ret = list.FindNum(x);
			if (ret != NULL)
			{
				list.Erase(ret);
			}
			else
			{
				cout << "您所查找的数据不存在" << endl;
			}
			break;
		case 0:
			break;
		default:
			cout << "您的输入错误" << endl;
			break;
		}
	}
}
int main()
{
	test();
	return 0;
}