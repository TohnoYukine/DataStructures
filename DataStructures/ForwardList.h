#pragma once
#include <stdexcept>

#define MAX_FORWARDLIST_SIZE 1073741824U;	//1GB

namespace DataStructures
{
	template<typename T>
	class ForwardList
	{
	private:
		struct ForwardListNode;
		class ForwardListIterator;
		class ForwardListConstIterator;

	public:
		using value_type		= T;
		using reference			= T&;
		using const_reference	= const T&;
		using pointer			= T*;
		using const_pointer		= const T*;
		using difference_type	= ptrdiff_t;
		using size_type			= size_t;

		using iterator			= ForwardListIterator;
		using const_iterator	= ForwardListConstIterator;

		//Constructor, Destructor and Assignment
		ForwardList() noexcept;
		explicit ForwardList(size_type n);
		ForwardList(size_type n, const T& val);

		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		ForwardList(InputIterator first, InputIterator last);

		ForwardList(std::initializer_list<T> init);
		ForwardList(const ForwardList<T>& origin);
		ForwardList(ForwardList<T> && origin) noexcept;
		~ForwardList();
		ForwardList<T>& operator=(const ForwardList<T>& origin);
		ForwardList<T>& operator=(ForwardList<T>&& origin);
		ForwardList<T>& operator=(std::initializer_list<T> origin);
		void assign(size_type n, const T& val);
		void assign(std::initializer_list<T> list);

		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		void assign(InputIterator first, InputIterator last);	//last not included

		//Element access
		reference front();

		//Iterators
		iterator begin() noexcept;
		const_iterator begin() const noexcept;
		const_iterator cbegin() const noexcept;
		iterator end() noexcept;
		const_iterator end() const noexcept;
		const_iterator cend() const noexcept;
		iterator before_begin() noexcept;
		const_iterator before_begin() const noexcept;
		const_iterator cbefore_begin() const noexcept;

		//Capacity
		bool empty() const noexcept;
		size_type max_size() const noexcept;
		//Standard does not provide size() to avoid overhead.

		//Modifiers
		void clear() noexcept;
		iterator insert_after(const_iterator pos, const T& val);
		iterator insert_after(const_iterator pos, T&& val);
		iterator insert_after(const_iterator pos, size_type n, const T& val);
		iterator insert_after(const_iterator pos, std::initializer_list<T> list);
		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		iterator insert_after(const_iterator pos, InputIterator first, InputIterator last);
		template <typename ... Args> iterator emplace_after(const_iterator pos, Args&& ... args);
		iterator erase_after(const_iterator pos);
		iterator erase_after(const_iterator first, const_iterator last);
		void push_front(const T& val);
		void push_front(T&& val);
		template <typename ... Args> reference emplace_front(Args&& ... args);
		void pop_front();
		void resize(size_type n);
		void resize(size_type n, const T& val);
		void swap(ForwardList<T>& other);
		//Standard does not provide insert() to avoid overhead.

		//Operations
		void merge(ForwardList& other);
		void merge(ForwardList&& other);
		template<typename Compare> void merge(ForwardList& other, Compare comp);
		template<typename Compare> void merge(ForwardList&& other, Compare comp);
		void splice_after(const_iterator pos, ForwardList& other);
		void splice_after(const_iterator pos, ForwardList&& other);
		void splice_after(const_iterator pos, ForwardList& other, const_iterator first);
		void splice_after(const_iterator pos, ForwardList&& other, const_iterator first);
		void splice_after(const_iterator pos, ForwardList& other, const_iterator first, const_iterator last);
		void splice_after(const_iterator pos, ForwardList&& other, const_iterator first, const_iterator last);
		void remove(const T& val);	//Remove all value equal to val
		template<typename UnaryPredicate> void remove_if(UnaryPredicate p);
		void reverse() noexcept;
		void unique();	//Remove all consecutive duplicate elements.
		template<typename BinaryPredicate> void unique(BinaryPredicate p);
		void sort();
		template<typename Compare> void sort(Compare comp);

		//Non-Standard Functions
		size_type size();	//O(n) algorithm. Traverse the list.
		iterator insert(const_iterator pos, const T& val);
		iterator insert(const_iterator pos, T&& val);
		iterator insert(const_iterator pos, size_type n, T& val);
		iterator insert(const_iterator pos, std::initializer_list<T> list);
		template<typename InputIterator, typename = typename std::enable_if_t<std::_Is_iterator<InputIterator>::value>>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last);
		template <typename ... Args> iterator emplace(const_iterator pos, Args&& ... args);
		iterator erase(const_iterator pos);
		iterator erase(const_iterator first, const_iterator last);
		void push_back(const T& val);
		void push_back(T&& val);
		template <typename ... Args> void emplace_back(Args&& ... args);
		void pop_back();
		reference back();	//O(n)
		iterator before_end() noexcept;
		const_iterator before_end() const noexcept;
		const_iterator cbefore_end() const noexcept;

		//Non-Member Functions
		template<typename T> friend bool operator==(const ForwardList<T>& lhs, const ForwardList<T>& rhs);
		template<typename T> friend bool operator!=(const ForwardList<T>& lhs, const ForwardList<T>& rhs);
		template<typename T> friend bool operator<(const ForwardList<T>& lhs, const ForwardList<T>& rhs);
		template<typename T> friend bool operator<=(const ForwardList<T>& lhs, const ForwardList<T>& rhs);
		template<typename T> friend bool operator>(const ForwardList<T>& lhs, const ForwardList<T>& rhs);
		template<typename T> friend bool operator>=(const ForwardList<T>& lhs, const ForwardList<T>& rhs);
		template<typename T> friend void swap(ForwardList<T>& lhs, ForwardList<T>& rhs);
		

	private:
		using node_type = ForwardListNode;
		//fore->first->...->last->end
		node_type head;
		node_type tail;	
		//Using nullptr as tail is silly. 
		//Using end() from one container for operations on another is runtime_error,
		//while using nullptr will hide this error.

	//Helper functions
	private:
		void move_after(iterator& from, iterator& to);	//Moves the node after "from" to after "to".
		void move_front(iterator& from);				//No check for from

	private:
		struct ForwardListNode
		{
			T value;
			ForwardListNode* next = nullptr;

			ForwardListNode() {}
			ForwardListNode(const T& val) : value(val) {}
			ForwardListNode(const T& val, ForwardListNode* p) : value(val), next(p) {}
			ForwardListNode(T&& val) : value(std::move(val)) {}
			ForwardListNode(T&& val, ForwardListNode* p) : value(std::move(val)), next(p) {}
			template<typename ...Args> ForwardListNode(ForwardListNode* p, Args && ...args) :
				value(std::forward<Args>(args)...), next(p) {}
		};
	
	public:
		class ForwardListIterator
		{
		public:
			using self_type = ForwardListIterator;
			using value_type = T;
			using reference = T&;
			using pointer = T*;
			using difference_type = ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			ForwardListIterator() {}
			ForwardListIterator(ForwardListNode* _p) : p(_p) {}
			ForwardListIterator(const ForwardListIterator& origin) : p(origin.p) {}
			ForwardListIterator& operator=(ForwardListIterator& origin) { p = origin.p; return *this; }

			ForwardListIterator& operator++() { p = p->next; return *this; }
			ForwardListIterator operator++(int) { ForwardListIterator ret(*this); ++*this; return ret; }
			bool operator==(const ForwardListIterator& rhs) const { return p == rhs.p; }
			bool operator!=(const ForwardListIterator& rhs) const { return p != rhs.p; }
			reference operator*() { return p->value; }
			reference operator*() const { return p->value; }	//Is this okay?
			pointer operator->() { return &p->value; }
			pointer operator->() const { return &p->value; }	//So does this?

		private:
			ForwardListIterator(const ForwardListConstIterator& origin) : p(const_cast<ForwardListNode*>(origin.p)) {}

		private:
			template<typename T> friend class ForwardList;
			ForwardListNode* p = nullptr;
		};

		class ForwardListConstIterator
		{
		public:
			using self_type = ForwardListConstIterator;
			using value_type = T;
			using reference = const T&;
			using pointer = const T*;
			using difference_type = ptrdiff_t;
			using iterator_category = std::forward_iterator_tag;

			ForwardListConstIterator() {}
			ForwardListConstIterator(const ForwardListNode* _p) : p(_p) {}
			ForwardListConstIterator(const ForwardListConstIterator& origin) : p(origin.p) {}
			ForwardListConstIterator(const ForwardListIterator& origin) : p(origin.p) {}
			ForwardListConstIterator& operator=(const ForwardListConstIterator& origin) { p = origin.p; return *this; }
			ForwardListConstIterator& operator=(const ForwardListIterator& origin) { p = origin.p; return *this; }

			ForwardListConstIterator& operator++() { p = p->next; return *this; }
			ForwardListConstIterator operator++(int) { ForwardListConstIterator ret(*this); ++*this; return ret; }
			bool operator==(const ForwardListConstIterator& rhs) const { return p == rhs.p; }
			bool operator!=(const ForwardListConstIterator& rhs) const { return p != rhs.p; }
			reference operator*() { return p->value; }
			reference operator*() const { return p->value; }	//Is this okay?
			pointer operator->() { return &p->value; }
			pointer operator->() const { return &p->value; }	//So does this?

		private:
			template<typename T> friend class ForwardList;
			const ForwardListNode* p = nullptr;
		};
	};

	/* Dividing Line (д├ бузе бу;)д├ (д├ бузе бу;)д├ (д├ бузе бу;)д├  */

	template<typename T>
	inline ForwardList<T>::ForwardList() noexcept 
	{
		head.next = &tail;
	}

	template<typename T>
	inline ForwardList<T>::ForwardList(size_type n) : ForwardList<T>()
	{
		//node_type* curr = &head;
		//for (size_t i = 0; i < n; i++)
		//{
		//	curr->next = new node_type();
		//	curr = curr->next;
		//}
		//curr->next = &tail;
		iterator curr = before_begin();
		for (size_t i = 0; i < n; i++)
		{
			curr.p->next = new node_type(T());
			++curr;
		}
		curr.p->next = end().p;
	}

	template<typename T>
	inline ForwardList<T>::ForwardList(size_type n, const T & val) : ForwardList<T>()
	{
		//node_type* curr = &head;
		//for (size_t i = 0; i < n; i++)
		//{
		//	curr->next = new node_type(val);
		//	curr = curr->next;
		//}
		//curr->next = &tail;
		iterator curr = before_begin();
		for (size_t i = 0; i < n; i++)
		{
			curr.p->next = new node_type(val);
			++curr;
		}
		curr.p->next = end().p;
	}

	template<typename T>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline ForwardList<T>::ForwardList(InputIterator first, InputIterator last) : ForwardList<T>()
	{
		//node_type* curr = &head;
		//while (first != last)
		//{
		//	curr->next = new node_type(*first++);
		//	curr = curr->next;
		//}
		//curr->next = &tail;
		iterator curr = before_begin();
		while (first != last)
		{
			curr.p->next = new node_type(*first++);
			++curr;
		}		
		curr.p->next = end().p;
	}

	template<typename T>
	inline ForwardList<T>::ForwardList(std::initializer_list<T> list) : 
		ForwardList(list.begin(), list.end())
	{
	}

	template<typename T>
	inline ForwardList<T>::ForwardList(const ForwardList<T>& origin) : 
		ForwardList(origin.cbegin(), origin.cend())
	{
	}

	template<typename T>
	inline ForwardList<T>::ForwardList(ForwardList<T>&& origin) noexcept
	{
		head.next = &tail;
		swap(origin);
	}

	template<typename T>
	inline ForwardList<T>::~ForwardList()
	{
		clear();
	}

	template<typename T>
	inline ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& origin)
	{
		swap(ForwardList<T>(origin));
		return *this;
	}

	template<typename T>
	inline ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& origin)
	{
		swap(origin);
		return *this;
	}

	template<typename T>
	inline ForwardList<T>& ForwardList<T>::operator=(std::initializer_list<T> origin)
	{
		swap(ForwardList<T>(origin));
		return *this;
	}

	template<typename T>
	inline void ForwardList<T>::assign(size_type n, const T & val)
	{
		swap(ForwardList<T>(n, val));
	}

	template<typename T>
	inline void ForwardList<T>::assign(std::initializer_list<T> init)
	{
		swap(ForwardList<T>(init));
	}

	template<typename T>
	inline typename ForwardList<T>::reference ForwardList<T>::front()
	{
		return *begin();
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::begin() noexcept
	{
		return iterator(head.next);
	}

	template<typename T>
	inline typename ForwardList<T>::const_iterator ForwardList<T>::begin() const noexcept
	{
		return const_iterator(head.next);
	}

	template<typename T>
	inline typename ForwardList<T>::const_iterator ForwardList<T>::cbegin() const noexcept
	{
		return const_iterator(head.next);
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::end() noexcept
	{
		return iterator(&tail);
	}

	template<typename T>
	inline typename ForwardList<T>::const_iterator ForwardList<T>::end() const noexcept
	{
		return const_iterator(&tail);
	}

	template<typename T>
	inline typename ForwardList<T>::const_iterator ForwardList<T>::cend() const noexcept
	{
		return const_iterator(&tail);
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::before_begin() noexcept
	{
		return iterator(&head);
	}

	template<typename T>
	inline typename ForwardList<T>::const_iterator ForwardList<T>::before_begin() const noexcept
	{
		return const_iterator(&head);
	}

	template<typename T>
	inline typename ForwardList<T>::const_iterator ForwardList<T>::cbefore_begin() const noexcept
	{
		return const_iterator(&head);
	}

	template<typename T>
	inline bool ForwardList<T>::empty() const noexcept
	{
		return begin() == end();
	}

	template<typename T>
	inline typename ForwardList<T>::size_type ForwardList<T>::max_size() const noexcept
	{
		return MAX_FORWARDLIST_SIZE;
	}

	template<typename T>
	inline void ForwardList<T>::clear() noexcept
	{
		//for (node_type* prev = head.next, *curr = prev->next; 
		//	curr->next != nullptr; prev = curr, curr = curr->next)
		//	delete prev;
		//head.next = &tail;
		for (iterator prev = begin(), curr = begin(); curr != end(); prev = curr)
		{
			curr++;
			delete prev.p;
		}
		head.next = &tail;
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, const T & val)
	{
		return emplace_after(pos, val);
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, T && val)
	{
		return emplace_after(pos, std::move(val));
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, size_type n, const T & val)
	{
		iterator ret(pos);
		for (size_t i = 0; i < n; i++)
			ret = emplace_after(ret, val);
		return ret;
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, std::initializer_list<T> list)
	{
		iterator ret(pos);
		for (const T& elem : list)
			ret = emplace_after(ret, elem);
		return ret;
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::erase_after(const_iterator pos)
	{
		iterator _next(pos);
		iterator _curr = _next++;
		_curr.p->next = _next.p->next;
		delete _next.p;
		return _curr;
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::erase_after(const_iterator first, const_iterator last)
	{
		iterator ret(first);
		iterator _last(last);
		while (ret.p->next != _last.p)
			ret = erase_after(ret);	//Must refresh first!
		return ret;
	}

	template<typename T>
	inline void ForwardList<T>::push_front(const T & val)
	{
		emplace_front(val);
	}

	template<typename T>
	inline void ForwardList<T>::push_front(T && val)
	{
		emplace_front(std::move(val));
	}

	template<typename T>
	inline void ForwardList<T>::pop_front()
	{
		erase_after(before_begin());
	}

	template<typename T>
	inline void ForwardList<T>::resize(size_type n)
	{
		size_type cnt = 0;
		iterator curr = begin();
		while (curr != end())
		{
			++cnt;
			if (cnt == n)
				curr = erase_after(curr, end());
			++curr;
		}
		for (size_t i = cnt; i < n; i++)
			curr = emplace_after(curr);
	}

	template<typename T>
	inline void ForwardList<T>::resize(size_type n, const T & val)
	{
		size_type cnt = 0;
		iterator curr = before_begin();
		while (true)
		{
			if (cnt == n)
			{
				curr = erase_after(curr, end());
				break;
			}
			if (curr.p->next == end().p)
				break;
			++cnt;
			++curr;
		}
		insert_after(curr, n - cnt, val);
	}

	template<typename T>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline void ForwardList<T>::assign(InputIterator first, InputIterator last)
	{
		swap(ForwardList<T>(first, last));
	}

	template<typename T>
	template<typename InputIterator, typename SFINAE_MAGIC>
	inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, InputIterator first, InputIterator last)
	{
		iterator ret(pos);
		while (first != last)
			ret = emplace_after(ret, *first++);
		return ret;
	}

	template<typename T>
	template<typename ...Args>
	inline typename ForwardList<T>::iterator ForwardList<T>::emplace_after(const_iterator pos, Args && ...args)
	{
		iterator _iter(pos);
		return _iter.p->next = new ForwardListNode(_iter.p->next, std::forward<Args>(args) ...);
		return _iter;
	}

	template<typename T>
	template<typename ...Args>
	inline typename ForwardList<T>::reference ForwardList<T>::emplace_front(Args && ...args)
	{
		return (head.next = new ForwardListNode(head.next, std::forward<Args>(args) ...))->value;
	}

	template<typename T>
	template<typename Compare>
	inline void ForwardList<T>::merge(ForwardList & other, Compare comp)
	{
		if (this == &other) return;
		if (other.empty()) return;
		if (empty())
		{
			swap(other);
			return;
		}

		iterator next_this = begin();
		iterator curr_this = next_this++;
		iterator curr_other = other.before_begin();
		iterator prev_other = curr_other++;

		//After this step, comp(*curr_other, *curr_this) == false is guaranteed.
		if (comp(*curr_other, *curr_this))
		{
			other.merge(*this, comp);
			swap(other);
			return;
		}

		while (next_this != end() && curr_other != other.end())
		{
			if (comp(*curr_other, *next_this))
			{
				++curr_other;
				move_after(prev_other, curr_this);
				++curr_this;
			}
			else
			{
				++curr_this;
				++next_this;
				continue;
			}
		}
		while (curr_other != other.end())
		{
			++curr_other;
			move_after(prev_other, curr_this);
			++curr_this;
		}
	}

	template<typename T>
	template<typename Compare>
	inline void ForwardList<T>::merge(ForwardList && other, Compare comp)
	{
		merge(other, comp);
	}

	template<typename T>
	template<typename UnaryPredicate>
	inline void ForwardList<T>::remove_if(UnaryPredicate p)
	{
		iterator curr = before_begin();
		iterator prev = curr++;
		while (curr != end())
		{
			if (p(*curr))
			{
				curr = erase_after(prev);
				prev = curr++;
			}
			else
			{
				++curr;
				++prev;
			}
		}
	}

	template<typename T>
	template<typename BinaryPredicate>
	inline void ForwardList<T>::unique(BinaryPredicate p)
	{
		if (empty()) return;
		iterator curr = begin();
		iterator prev = curr++;
		while (curr != end())
		{
			if (p(*curr, *prev))
				curr = erase_after(prev);
			prev = curr++;
		}
	}

	template<typename T>
	inline void ForwardList<T>::swap(ForwardList<T>& other)
	{
		if (!empty() && !other.empty())
		{
			//Swap the tail first, finding the before tail node needs the head!
			std::swap(before_end().p->next, other.before_end().p->next);
			std::swap(head.next, other.head.next);
		}
		else if (empty() && other.empty())
		{
			return;
		}
		else if (empty())
		{
			other.before_end().p->next = &tail;
			head.next = other.head.next;
			other.head.next = &other.tail;
		}
		else	//Only other is empty
		{
			before_end().p->next = &other.tail;
			other.head.next = head.next;
			head.next = &tail;
		}
	}

	template<typename T>
	inline void ForwardList<T>::merge(ForwardList & other)
	{
		merge(other, std::less<T>());
	}

	template<typename T>
	inline void ForwardList<T>::merge(ForwardList && other)
	{
		merge(other, std::less<T>());
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::before_end() noexcept
	{
		iterator curr = before_begin();
		while (curr.p->next != end().p) 
			++curr;
		return curr;
	}

	template<typename T>
	inline typename ForwardList<T>::const_iterator ForwardList<T>::before_end() const noexcept
	{
		const_iterator curr = cbefore_begin();
		while (curr.p->next != cend().p) ++curr;
		return curr;
	}

	template<typename T>
	inline typename ForwardList<T>::const_iterator ForwardList<T>::cbefore_end() const noexcept
	{
		const_iterator curr = cbefore_begin();
		while (curr.p->next != cend().p) ++curr;
		return curr;
	}

	template<typename T>
	inline void ForwardList<T>::move_after(iterator & from, iterator & to)
	{
		iterator temp(from.p->next->next);
		from.p->next->next = to.p->next;
		to.p->next = from.p->next;
		from.p->next = temp.p;
		//from and to still at original position
	}

	template<typename T>
	inline void ForwardList<T>::move_front(iterator & from)
	{
		iterator temp(from.p->next->next);
		from.p->next->next = begin().p;
		head.next = from.p->next;
		from.p->next = temp.p;
	}

	template<typename T>
	inline void ForwardList<T>::splice_after(const_iterator pos, ForwardList & other)
	{
		if (this == &other) return;
		splice_after(pos, other, other.before_begin());
	}

	template<typename T>
	inline void ForwardList<T>::splice_after(const_iterator pos, ForwardList && other)
	{
		splice_after(pos, other);
	}

	template<typename T>
	inline void ForwardList<T>::splice_after(const_iterator pos, ForwardList & other, const_iterator first)
	{
		if (pos == first || pos == ++(const_iterator(first))) return;
		splice_after(pos, other, first, other.cend());
	}

	template<typename T>
	inline void ForwardList<T>::splice_after(const_iterator pos, ForwardList && other, const_iterator first)
	{
		splice_after(pos, other, first);
	}

	template<typename T>
	inline void ForwardList<T>::splice_after(const_iterator pos, ForwardList & other, const_iterator first, const_iterator last)
	{
		iterator _next(pos);
		iterator _curr = _next++;
		iterator _first(first);
		iterator _last(last);
		_curr.p->next = _first.p->next;
		while (_curr.p->next != _last.p) ++_curr;
		_curr.p->next = _next.p;
		_first.p->next = _last.p;
	}

	template<typename T>
	inline void ForwardList<T>::splice_after(const_iterator pos, ForwardList && other, const_iterator first, const_iterator last)
	{
		splice_after(pos, other, first, last);
	}

	template<typename T>
	inline void ForwardList<T>::remove(const T & val)
	{
		remove_if([&val](const T& elem) { return std::equal_to<T>()(val, elem); });
	}

	template<typename T>
	inline void ForwardList<T>::reverse() noexcept
	{
		if (empty()) return;
		iterator curr = begin();
		while (curr.p->next != end().p)
			move_front(curr);
	}

	template<typename T>
	inline void ForwardList<T>::unique()
	{
		unique(std::equal_to<T>());
	}
}