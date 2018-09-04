/*
	名称: 双向循环链表模板类
	作者: Kevin
	创建日期: 2018/09/03 22:45
	当前最高版本: 0.0.1

	0.0 概况:
	  -0 链表的首版本
	  -1 实现链表的基本操作
	  -2 没有实现迭代器

	0.0.1 更新日志:		2018/09/04  23:56
	  -0 修改了一些函数的接口（添加部分 const、将部分 Type 值传递改为引用传递）
	  -1 新增加了链表的反转操作
	  -2 新增加了链表的插入操作（插入到某个位置）
	  -3 新增加了链表的查找操作（按值查找、按位置查找）
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
			Node(const Type &data) : data(data) { }
			Node(Node *prev, Node *next, const Type &data) :
				prev(prev), next(next), data(data) { }
		};

		// 基础变量:
		unsigned int cnt;	// 记录链表当前结点个数
		Node *head;			// 链表头指针
		Node *tail;			// 链表尾指针

	private:

		inline void swap_pNode(Node *&p, Node *&q)
		{
			Node *temp = p;
			p = q;
			q = temp;
		}

		// 向空链表中插入第一个结点
		inline void push_first(const Type &first_data)
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
		inline void insert_prev(Node *pNode, const Type &data)
		{
			Node *pNewNode = new Node(pNode->prev, pNode, data);
			pNode->prev->next = pNewNode;
			pNode->prev = pNewNode;
			cnt++;
		}

		// 向指针指向结点之后插入节点
		inline void insert_next(Node *pNode, const Type &data)
		{
			Node *pNewNode = new Node(pNode, pNode->next, data);
			pNode->next->prev = pNewNode;
			pNode->next = pNewNode;
			cnt++;
		}

	public:

		Klist(void) : cnt(0), head(nullptr), tail(nullptr) { }

		Klist(const Type *array, const unsigned int len)
		{
			push_first(array[0]);		// 向空链表内插入第一个结点
			for (int i=1; i<len; ++i)	// 按序插入剩下的结点
			{
				push_back(array[i]);
			}
		}

		~Klist(void)
		{
			clear();
		}

		inline bool empty(void)
		{
			return 0 == cnt;
		}

		inline unsigned int size(void)
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

		// 顺序打印链表（结点数据需要支持 std::cout）
		void print(void)
		{
			if (cnt)	// 链表不空，才可打印
			{
				for (Node *p=head; p!=tail; p=p->next)
				{
					std::cout << p->data << " <-> ";
				}
				std::cout << tail->data << std::endl;
			}
		}

		// 逆序打印链表（结点数据需要支持 std::cout）
		void rprint(void)
		{
			if (cnt)	// 链表不空，才可打印
			{
				for (Node *p=tail; p!=head; p=p->prev)
				{
					std::cout << p->data << " <-> ";
				}
				std::cout << head->data << std::endl;
			}
		}
		
		// 查找值的首次出现位置，找不到返回 -1 
		int find(const Type &object)
		{
			int pos = -1;
			if (cnt)	// 链表不空，才可查找
			{
				unsigned int nowPos = 0;
				for (Node *p=head; p!=tail; p=p->next, ++nowPos)
				{
					if (object == p->data)
					{
						pos = nowPos;
						break;
					}
				}
				if ( -1 == pos && object == tail->data )
				{
					pos = cnt-1;
				}
			}
			return pos;
		}

		// 查找值的最后一次出现位置，找不到返回 -1 
		int rfind(const Type &object)
		{
			int pos = -1;
			if (cnt)	// 链表不空，才可查找
			{
				unsigned int nowPos = cnt-1;
				for (Node *p=tail; p!=head; p=p->prev, --nowPos)
				{
					if (object == p->data)
					{
						pos = nowPos;
						break;
					}
				}
				if ( -1 == pos && object == head->data )
				{
					pos = 0;
				}
			}
			return pos;
		}

		// 反转整个链表
		void reverse()
		{
			if (cnt)	// 链表不空，才可反转
			{
				// 把每一个结点的 prev 和 next 指针交换
				for (Node *now=head; now!=tail; now=now->prev)
				{
					swap_pNode(now->prev, now->next);
				}
				swap_pNode(tail->prev, tail->next);

				// 把链表的 head 和 tail 指针交换
				swap_pNode(head, tail);
			}
		}

		void push_front(const Type &data)
		{
			if (cnt)	// 链表不空，正常头插
			{
				insert_prev(head, data);
				head = head->prev;
			}
			else		// 否则向空链表中插入第一个结点 
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
			else		// 否则向空链表中插入第一个结点 
			{
				push_first(data);
			}
		}

		void pop_front(void)
		{
			if ( 1 == cnt )		// 链表只有一个元素
			{
				pop_last();
			}
			else if ( 1 < cnt )	// 链表不只有一个结点，正常删除头结点
			{
				Node *oldHead = head;
				head = head->next;
				delete_node(oldHead);
			}
		}

		void pop_back(void)
		{
			if ( 1 == cnt )		// 链表只有一个元素
			{
				pop_last();
			}
			else if ( 1 < cnt )	// 链表不只有一个结点，正常删除尾结点
			{
				Node *oldTail = tail;
				tail = tail->prev;
				delete_node(oldTail);
			}
		}

		void insert(const unsigned int pos, const Type &data)
		{
			if ( 0 == pos )			// 插入在链表头
			{
				push_front(data);
			}
			else if ( pos < cnt )	// 插入在链表中的某个位置
			{
				Node *now = head;
				for (unsigned int nowPos = 0; pos!=nowPos; ++nowPos)
				{
					now=now->next;
				}
				insert_prev(now, data);	// 因为新结点要取代 now 所指的结点的位置，所以新节点要插入在 now 结点之前
			}
			else if ( pos == cnt )
			{
				push_back(data);	// 插入在链表尾
			}
		}
		
		const Type &at(const unsigned int pos)
		{
			if (cnt)					// 链表不空，才可取值 
			{
				if ( 0 == pos )			// 取得链表头的数据 
				{
					return head->data;
				}
				else if ( pos < cnt )	// 取得链表中某个位置的数据 
				{
					Node *now = head;
					for (unsigned int nowPos = 0; pos!=nowPos; ++nowPos)
					{
						now=now->next;
					}
					return now->data;
				}
				else if ( pos == cnt )
				{
					return tail->data;	// 取得链表尾的数据 
				}
			}
		}
};

}	// namespace kstl

#endif	// INC_KLIST
