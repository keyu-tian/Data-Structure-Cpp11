/*
	名称: 双向循环链表模板类
	作者: Kevin
	日期: 04/09/17 22:45
	版本: 0.0.0
	更新描述:
		-0 链表的首版本
		-1 实现了链表的基本插入、删除、清除操作
		-2 没有实现迭代器
*/

#ifndef INC_KLIST
#define INC_KLIST

#include <iostream>

namespace kstl
{

template <typename Type>
class Klist
{
	private:

		// 内部类：链表的结点
		class Node
		{
			friend class Klist;
			private:
				Type data;
				Node *prev;
				Node *next;

				Node(void) { }
				Node(Type data) : data(data) { }
				Node(Node *prev, Node *next, Type data) :
					prev(prev), next(next), data(data) { }
		};

		// 基础变量
		unsigned int cnt;	// 记录链表当前结点个数
		Node *head;			// 链表头指针
		Node *tail;			// 链表尾指针

		// 私有的操作函数：插入第一个结点、删除最后一个结点、删除某结点、在某结点之前或之后插入新节点
		inline void push_first(Type first_data)
		{
			Node *pNewNode = new Node(first_data);
			pNewNode->next = pNewNode->prev = pNewNode;
			head = tail = pNewNode;
			cnt = 1;
		}

		inline void pop_last(void)
		{
			delete head;
			head = tail = nullptr;
			cnt = 0;
		}

		inline void delete_node(Node *pNode)
		{
			pNode->prev->next = pNode->next;
			pNode->next->prev = pNode->prev;

			delete pNode;
			--cnt;
		}

		inline void insert_prev(Node *pNode, Type data)
		{
			Node *pNewNode = new Node(pNode->prev, pNode, data);
			pNode->prev->next = pNewNode;
			pNode->prev = pNewNode;
			cnt++;
		}

		inline void insert_next(Node *pNode, Type data)
		{
			Node *pNewNode = new Node(pNode, pNode->next, data);
			pNode->next->prev = pNewNode;
			pNode->next = pNewNode;
			cnt++;
		}


	public:

		// 构造析构函数
		Klist(void) : cnt(0), head(nullptr), tail(nullptr) { }

		Klist(Type *array, unsigned int len)
		{
			push_first(array[0]);		// 用第一个数据初始化链表
			for(int i=1; i<len; i++)	// 按序插入剩下的数据
			{
				push_back(array[i]);
			}
		}

		~Klist(void)
		{
			clear();
		}

		// 功能函数：结点的插入、链表的判断空、返回个数、获取头尾数据、打印（需支持std::cout）清除
		bool empty(void)
		{
			return cnt == 0;
		}

		unsigned int size(void)
		{
			return cnt;
		}

		const Type &front(void)
		{
			if (cnt)	// 链表不空，才可获取
			{
				return head->data;
			}
		}

		const Type &back(void)
		{
			if (cnt)	// 链表不空，才可获取
			{
				return tail->data;
			}
		}

		void clear(void)
		{
			if (cnt)	// 链表不空，才需清除
			{
				for (Node *now=head, *next; now!=tail; now=next)
				{
					next = now->next;
					delete now;
				}
				delete tail;
			}
		}

		void print(void)
		{
			if (cnt)	// 链表不空，才可打印
			{
				for(Node *p=head; p!=tail; p=p->next)
				{
					std::cout << p->data << " <-> ";
				}
				std::cout << tail->data << std::endl;
			}
		}

		void rprint(void)
		{
			if (cnt)	// 链表不空，才可打印
			{
				for(Node *p=tail; p!=head; p=p->prev)
				{
					std::cout << p->data << " <-> ";
				}
				std::cout << head->data << std::endl;
			}
		}

		// 两端增删函数：头尾插入、头尾删除
		void push_front(const Type &data)
		{
			if (cnt)	// 链表不空，正常头插
			{
				insert_prev(head, data);
				head = head->prev;
			}
			else		// 否则用data初始化链表
			{
				push_first(data);
			}
		}

		void push_back(const Type &data)
		{
			if (cnt)	// 链表不空，正常尾插
			{
				insert_next(tail, data);
				tail = tail->next;
			}
			else		// 否则用data初始化链表
			{
				push_first(data);
			}
		}

		void pop_front(void)
		{
			if ( 1==cnt )	// 链表只有一个元素
			{
				pop_last();
			}
			else if (1<cnt)	// 链表不只有一个结点，正常删除头结点
			{
				Node *oldHead = head;
				head = head->next;
				delete_node(oldHead);
			}
		}

		void pop_back(void)
		{
			if ( 1==cnt )	// 链表只有一个元素
			{
				pop_last();
			}
			else if (1<cnt)	// 链表不只有一个结点，正常删除尾结点
			{
				Node *oldTail = tail;
				tail = tail->prev;
				delete_node(oldTail);
			}
		}
};

}	// namespace kstl

#endif	// INC_KLIST
