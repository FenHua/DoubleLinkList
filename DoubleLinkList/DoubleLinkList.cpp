// DoubleLinkList.cpp : �������̨Ӧ�ó������ڵ㡣
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
			//������
			cout << "����գ�����βɾ����" << endl;
			return;
		}
		else if (_head == _tail)
		{
			//ֻ��һ���ڵ�
			delete _tail;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			//���ڵ�����
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
		_head = NewNode;//ͷָ��
	}
	void PopFront()
	{
		if (!_head&&!_tail)
		{
			//��
			cout << "����Ϊ�գ�����ͷɾ��" << endl;
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
			//��������
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
		//��ָ��λ�ú����Ԫ��
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
			//�ڵ�һ�����ǰ����
			NewNode->_next = pos;
			pos->_front = NewNode;
			_head = NewNode;
		}
	}
	void Insert(int, Node*pos, DataType x)
	{
		//��ָ��λ�ú����
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
			_head = NewNode;//����ͷ
		}
	}
	void Remove(DataType &x)
	{
		Node*pos = this->FindNum(x);
		if (pos != NULL)
		{
			if ((!(pos->_front)) && (pos->_next))
			{
				//ɾ����һ�����
				Node*tmp = pos->_next;
				tmp->_front = NULL;
				_head = tmp;
			}
			else
			{
				//ɾ�����������м�
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
			//ɾ����һ���ڵ�
			Node*tmp = pos->_next;
			tmp->_front = NULL;
			_head = tmp;
		}
		else if (pos->_front && (!(pos->_next)))
		{
			//ɾ�����һ���ڵ�
			Node*tmp = pos->_front;
			tmp->_next = NULL;
			_tail = tmp;
		}
		else
		{
			//ɾ���м�ڵ�
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
	cout << "************1.β��************2.βɾ**************" << endl;
	cout << "************3.ͷ��************4.ͷɾ**************" << endl;
	cout << "************5.ָ��λ�ú��****6.ָ��λ��ǰ��******" << endl;
	cout << "************7.ɾ��ָ��Ԫ��****8.ɾ������ָ��Ԫ��**" << endl;
	cout << "************9.����************0.�˳�*************" << endl;
	cout << "************11.Erase**********0.�˳�*************" << endl;
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
		cout << "����ѡ�";
		cin >> input;
		switch (input)
		{
		case 1:
			cout << "������Ҫ��������ݣ�";
			cin >> x;
			list.PushBack(x);
			break;
		case 2:
			list.PopBack();
			break;
		case 3:
			cout << "��������Ҫ���������>";
			cin >> x;
			list.PushFront(x);
			break;
		case 4:
			list.PopFront();
			break;
		case 5:
			cout << "��������Ҫ���ҵ�����>";
			cin >> x;
			ret = list.FindNum(x);
			if (ret != NULL)
			{
				cout << "��������Ҫ���������>";
				cin >> num;
				list.Insert(ret, num);
			}
			else
			{
				cout << "�������ҵ����ݲ�����" << endl;
			}
			break;
		case 6:
			cout << "��������Ҫ���ҵ�����>";
			cin >> x;
			ret = list.FindNum(x);
			if (ret != NULL)
			{
				cout << "��������Ҫ���������>";
				cin >> num;
				list.Insert(0, ret, num);  //0����ռλ����������  
			}
			else
			{
				cout << "�������ҵ����ݲ�����" << endl;
			}
			break;
		case 7:
			cout << "��������Ҫɾ��������>";
			cin >> x;
			list.Remove(x);
			break;
		case 8:
			cout << "��������Ҫɾ��������>";
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
			cout << "��������Ҫ����������>";
			cin >> x;
			ret = list.FindNum(x);
			if (ret != NULL)
			{
				list.Erase(ret);
			}
			else
			{
				cout << "�������ҵ����ݲ�����" << endl;
			}
			break;
		case 0:
			break;
		default:
			cout << "�����������" << endl;
			break;
		}
	}
}
int main()
{
	test();
	return 0;
}