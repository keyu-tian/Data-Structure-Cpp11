/*
	名称: 双向循环链表模板类
	作者: Kevin
	创建日期: 2018/09/03 22:45
	当前最高版本: 0.0.3

	0.0 概况:
	  -0 链表的首版本
	  -1 实现链表的基本操作
	  -2 没有实现迭代器

	0.0.3 更新日志:		2018/09/05  19:47
	  -0 重构了代码，将之前的部分 for 循环修改为 do-while
	  -1 重构了代码，将之前一些基于 pos 的函数进行了效率优化（如果 pos 在后半部分则从尾部开始往前遍历）
      -2 新增加了链表的构造函数（指定数目和数据）
	  -3 新增加了链表的插入操作（指定位置）
      -4 新增加了链表的删除操作（指定单个位置、指定区域）
*/

#ifndef INC_KLIST
#define INC_KLIST

#include <iostream>
#include <cstdlib>

#define k_assert(_expression, _information) \
	(void) ( (_expression) || (_k_assert(_information, __FILE__, __LINE__, __func__), 0) )

#define _k_assert(_information, _file, _line, _func) \
	std::cerr << "error in "  << _file			\
	          << ", function " << _func 		\
	          << ", line "     << _line 		\
	          << " : " << _information << '\n',	\
	          std::exit(0)

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

		// 删除单结点链表的唯一结点
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

		// 向指针指向结点之前插入结点
		inline void insert_prev(Node *pNode, const Type &data)
		{
			Node *pNewNode = new Node(pNode->prev, pNode, data);
			pNode->prev->next = pNewNode;
			pNode->prev = pNewNode;
			cnt++;
		}

		// 向指针指向结点之后插入结点
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

		Klist(const unsigned int count, const Type &data)
		{
			push_first(data);			// 向空链表内插入第一个结点
			for (int i=1; i<count; ++i)	// 插入剩下的结点
			{
				push_back(data);
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

		inline const Type &front(void)
		{
			k_assert(0 != cnt, "Klist empty(front)");		// 空链表不能获取
			return head->data;
		}

		inline const Type &back(void)
		{
			k_assert(0 != cnt, "Klist empty(back)");		// 空链表不能获取
			return tail->data;
		}

		void clear(void)
		{
			if (0 != cnt)	// 链表不空，才需清除
			{
				Node *now = head, *next;
				do
				{
					next = now->next;
					delete now;
					now = next;
				}
				while ( now != head );

				head = tail = nullptr;
				cnt = 0;
			}
		}

		// 顺序打印链表（结点数据需要支持 std::cout）
		void print(void)
		{
			if (0 != cnt)	// 链表不空，才需打印
			{
				Node *now = head;
				do
				{
					std::cout << now->data << ' ';
					now = now->next;
				}
				while ( now != head );
				std::cout << std::endl;
			}
		}

		// 逆序打印链表（结点数据需要支持 std::cout）
		void rprint(void)
		{
			if (0 != cnt)	// 链表不空，才需打印
			{
				Node *now = tail;
				do
				{
					std::cout << now->data << ' ';
					now = now->prev;
				}
				while ( now != tail );
				std::cout << std::endl;
			}
		}

		// 查找值的首次出现位置，找不到返回 -1
		int find(const Type &object)
		{
			int pos = -1;
			if (0 != cnt)	// 链表不空，才需查找
			{
				unsigned int nowPos = 0;
				Node *now = head;
				do
				{
					if ( object == now->data )
					{
						pos = nowPos;
						break;
					}
					now = now->next;
					++nowPos;
				}
				while( now != head );
			}
			return pos;
		}

		// 查找值的最后一次出现位置，找不到返回 -1
		int rfind(const Type &object)
		{
			int pos = -1;
			if (0 != cnt)	// 链表不空，才需查找
			{
				unsigned int nowPos = cnt-1;
				Node *now = tail;
				do
				{
					if ( object == now->data )
					{
						pos = nowPos;
						break;
					}
					now = now->prev;
					--nowPos;
				}
				while( now != tail );
			}
			return pos;
		}

		// 反转整个链表
		void reverse()
		{
			if (0 != cnt)	// 链表不空，才需反转
			{
				// 把每一个结点的 prev 和 next 指针交换
				Node *now = head;
				do
				{
					swap_pNode(now->prev, now->next);
					now = now->prev;
				}
				while ( now != head );

				// 把链表的 head 和 tail 指针交换
				swap_pNode(head, tail);
			}
		}

		void push_front(const Type &data)
		{
			if (0 != cnt)	// 链表不空，正常头插
			{
				insert_prev(head, data);
				head = head->prev;
			}
			else			// 否则向空链表中插入第一个结点
			{
				push_first(data);
			}
		}

		void push_back(const Type &data)
		{
			if (0 != cnt)	// 链表不空，正常尾插
			{
				insert_next(tail, data);
				tail = tail->next;
			}
			else			// 否则向空链表中插入第一个结点
			{
				push_first(data);
			}
		}

		void pop_front(void)
		{
			k_assert(0 != cnt, "Klist empty(pop)");	// 空链表不能 pop

			if ( 1 == cnt )		// 链表只有一个结点，删除它
			{
				pop_last();
			}
			else				// 链表不只有一个结点，正常删除头结点
			{
				Node *oldHead = head;
				head = head->next;
				delete_node(oldHead);
			}
		}

		void pop_back(void)
		{
			k_assert(0 != cnt, "Klist empty(pop)");	// 空链表不能 pop

			if ( 1 == cnt )		// 链表只有一个结点，删除它
			{
				pop_last();
			}
			else				// 链表不只有一个结点，正常删除尾结点
			{
				Node *oldTail = tail;
				tail = tail->prev;
				delete_node(oldTail);
			}
		}

		const Type &at(const unsigned int pos)
		{
			k_assert( 0 != cnt, "Klist empty(at)");			// 空链表不可取值
			k_assert(pos < cnt, "Klist out of range(at)");	// 越界，不可取值

			Node *now;
			if ( pos < cnt/2 )	// 目标位置在链表前半部分
			{
				now = head;
				for (unsigned int nowPos = 0; pos!=nowPos; ++nowPos)
				{
					now = now->next;
				}
			}
			else				// 目标位置在链表后半部分
			{
				now = tail;
				for (unsigned int nowPos = cnt-1; pos!=nowPos; --nowPos)
				{
					now = now->prev;
				}
			}

			return now->data;
		}

		void insert(const unsigned int pos, const Type &data)
		{
			k_assert(pos <= cnt, "Klist out of range(insert)");	// 越界，不可插入

			if ( 0 == pos )				// 插入在链表头之前
			{
				push_front(data);
			}
			else if ( pos < cnt/2 )		// 插入在链表的前半部分（不包含链表头之前）
			{
				Node *now = head;
				for (unsigned int nowPos = 0; pos!=nowPos; ++nowPos)
				{
					now = now->next;
				}
				insert_prev(now, data);
			}
			else if ( pos < cnt )		// 插入在链表的后半部分（不包含链表尾之后）
			{
				Node *now = tail;
				for (unsigned int nowPos = cnt-1; pos!=nowPos; --nowPos)
				{
					now = now->prev;
				}
				insert_prev(now, data);
			}
			else						// 插入在链表尾之后
			{
				push_back(data);
			}
		}

		void erase(const unsigned int pos)
		{
			k_assert( 0 != cnt, "Klist empty(erase)");			// 空链表不可删除
			k_assert(pos < cnt, "Klist out of range(erase)");	// 越界，不可删除

			if ( 0 == pos )				// 删除链表头
			{
				pop_front();
			}
			else if ( pos < cnt/2 )		// 删除链表前半部分某个位置（不包括链表头）
			{
				Node *now = head;
				for (unsigned int nowPos = 0; pos!=nowPos; ++nowPos)
				{
					now = now->next;
				}
				delete_node(now);
			}
			else if ( pos < cnt-1 )		// 删除链表后半部分某个位置（不包括链表尾）
			{
				Node *now = tail;
				for (unsigned int nowPos = cnt-1; pos!=nowPos; --nowPos)
				{
					now = now->prev;
				}
				delete_node(now);
			}
			else						// 删除链表尾
			{
				pop_back();
			}
		}

		void erase(const unsigned int firstPos, const unsigned int lastPos)	// 闭区间
		{
			k_assert(0 != cnt, "Klist empty(erase)");						// 空链表不可删除
			k_assert(lastPos < cnt, "Klist out of range(erase)");			// 越界，不可删除
			k_assert(firstPos <= lastPos, "Klist invalid input(erase)");	// 输入不合法，不可删除

			if ( 0 == firstPos && cnt-1 == lastPos)		// 删除整个链表
			{
				clear();
			}
			else if ( 0 == firstPos && cnt-1 > lastPos)	// 删除包含链表头而不包含链表尾的一部分
			{
				Node *now = head, *next;
				for (unsigned int nowPos=0; nowPos<=lastPos; ++nowPos)
				{
					next = now->next;
					delete now;
					--cnt;
					now = next;
				}

				head = now;
				head->prev = tail;
				tail->next = head;
			}
			else if ( 0 < firstPos && cnt-1 == lastPos)	// 删除包含链表尾而不包含链表头的一部分
			{
				Node *now = tail, *prev;
				for (unsigned int nowPos=cnt-1; nowPos>=firstPos; --nowPos)
				{
					prev = now->prev;
					delete now;
					--cnt;
					now = prev;
				}

				tail = now;
				tail->next = head;
				head->prev = tail;
			}
			else if ( firstPos - 0 < cnt-1 - lastPos )	// 删除区域更靠前（不包含链表头尾）
			{
				Node *now = head, *next, *firstPosPrev, *lastPosNext;
				unsigned int nowPos = 0;
				while ( nowPos < firstPos )
				{
					now = now->next;
					++nowPos;
				}

				firstPosPrev = now->prev;
				for (; nowPos<=lastPos; ++nowPos)
				{
					next = now->next;
					delete now;
					--cnt;
					now = next;
				}
				lastPosNext = now;

				firstPosPrev->next = lastPosNext;
				lastPosNext->prev  = firstPosPrev;
			}
			else										// 删除区域更靠后（不包含链表头尾）
			{
				Node *now = tail, *prev, *firstPosPrev, *lastPosNext;
				unsigned int nowPos = cnt-1;
				while ( nowPos > lastPos )
				{
					now = now->prev;
					--nowPos;
				}

				lastPosNext = now->next;
				for (; nowPos>=firstPos; --nowPos)
				{
					prev = now->prev;
					delete now;
					--cnt;
					now = prev;
				}
				firstPosPrev = now;

				firstPosPrev->next = lastPosNext;
				lastPosNext->prev  = firstPosPrev;
			}
		}
};

}	// namespace kstl

#endif	// INC_KLIST
