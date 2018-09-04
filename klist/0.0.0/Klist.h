/*
	名称: 双向循环链表模板类
	作者: Kevin
	创建日期: 17/09/03 22:45
	当前最高版本: 0.0.0

	0.0 概况:
	  -0 链表的首版本
	  -1 实现链表的基本操作
	  -2 没有实现迭代器

	0.0.0 更新:		2018/09/03  23:07
		-0 新增加了链表的构造、析构函数
		-1 新增加了链表的判断空和获取结点个数函数
		-2 新增加了链表的获取头尾数据函数
		-3 新增加了链表的清空、顺序打印、逆序打印函数
		-4 新增加了链表的头尾增删操作函数 
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
		struct Node
		{
			Type data;
			Node *prev;
			Node *next;

			Node(void) { }
			Node(Type data) : data(data) { }
			Node(Node *prev, Node *next, Type data) :
				prev(prev), next(next), data(data) { }
		};

		// 基础变量:
		unsigned int cnt;	// 记录链表当前结点个数
		Node *head;			// 链表头指针
		Node *tail;			// 链表尾指针

	private:

		// 向空链表中插入第一个结点
		inline void push_first(Type first_data)
		{
			Node *pNewNode = new Node(first_data);
			pNewNode->next = pNewNode->prev = pNewNode;
			head = tail = pNewNode;
			cnt = 1;
		}

		// 删除单节点链表的唯一结点
		inline void pop_last(void)
		{
			delete head;
			head = tail = nullptr;
			cnt = 0;
		}

		// 删除指针指向的结点
		inline void delete_node(Node *pNode)
		{
			pNode->prev->next = pNode->next;
			pNode->next->prev = pNode->prev;

			delete pNode;
			--cnt;
		}

		// 向指针指向结点之前插入节点
		inline void insert_prev(Node *pNode, Type data)
		{
			Node *pNewNode = new Node(pNode->prev, pNode, data);
			pNode->prev->next = pNewNode;
			pNode->prev = pNewNode;
			cnt++;
		}

		// 向指针指向结点之后插入节点
		inline void insert_next(Node *pNode, Type data)
		{
			Node *pNewNode = new Node(pNode, pNode->next, data);
			pNode->next->prev = pNewNode;
			pNode->next = pNewNode;
			cnt++;
		}

	public:

		Klist(void) : cnt(0), head(nullptr), tail(nullptr) { }

		Klist(Type *array, unsigned int len)
		{
			push_first(array[0]);		// 向空链表内插入第一个结点
			for(int i=1; i<len; i++)	// 按序插入剩下的结点
			{
				push_back(array[i]);
			}
		}

		~Klist(void)
		{
			clear();
		}

		bool empty(void)
		{
			return 0 == cnt;
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

		// 整个打印链表（结点数据需要支持 std::cout）
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

		// 逆序打印整个链表（结点数据需要支持 std::cout）
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
			if ( 1==cnt )		// 链表只有一个元素
			{
				pop_last();
			}
			else if ( 1<cnt )	// 链表不只有一个结点，正常删除头结点
			{
				Node *oldHead = head;
				head = head->next;
				delete_node(oldHead);
			}
		}

		void pop_back(void)
		{
			if ( 1==cnt )		// 链表只有一个元素
			{
				pop_last();
			}
			else if ( 1<cnt )	// 链表不只有一个结点，正常删除尾结点
			{
				Node *oldTail = tail;
				tail = tail->prev;
				delete_node(oldTail);
			}
		}
};

}	// namespace kstl

#endif	// INC_KLIST
