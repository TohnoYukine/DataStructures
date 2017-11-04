#pragma once
#include <stdexcept>

#define MAX_FORWARDLIST_SIZE 1073741824U;	//1GB

namespace DataStructures
{
	template<class T> struct ForwardListNode;
	template<typename T> class ForwardListIterator;
	template<typename T> class ForwardListConstIterator;

	template<typename T>
	class ForwardList
	{
	public:
		using value_type		= T;
		using reference			= T&;
		using const_reference	= const T&;
		using pointer			= T*;
		using const_pointer		= const T*;
		using difference_type	= ptrdiff_t;
		using size_type			= size_t;

		using iterator			= ForwardListIterator<T>;
		using const_iterator	= ForwardListConstIterator<T>;

		//Constructor, Destructor and Assignment
		ForwardList() noexcept;
		explicit ForwardList(size_type n);
		ForwardList(size_type n, const T& val);
		ForwardList(const_iterator first, const_iterator last);
		ForwardList(std::initializer_list<T> list);
		ForwardList(const ForwardList<T>& origin);
		ForwardList(ForwardList<T> && origin) noexcept;
		~ForwardList();
		ForwardList<T>& operator=(ForwardList<T> origin);
		ForwardList<T>& operator=(ForwardList<T>&& origin);
		ForwardList<T>& operator=(std::initializer_list<T> origin);
		void assign(size_type n, const T& val);
		void assign(std::initializer_list<T> list);
		template<class InputIterator> void assign(InputIterator first, InputIterator last);	//last not included

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
		iterator insert_after(const_iterator pos, size_type n, T& val);
		iterator insert_after(const_iterator pos, std::initializer_list<T> list);
		template<typename InputIterator> iterator insert_after(const_iterator pos, InputIterator first, InputIterator last);
		template <typename ... Args> iterator emplace_after(const_iterator pos, Args&& ... args);
		iterator erase_after(const_iterator pos);
		iterator erase_after(const_iterator first, const_iterator last);
		void push_front(const T& val);
		void push_front(T&& val);
		template <typename ... Args> void emplace_front(Args&& ... args);
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
		template<typename InputIterator> iterator insert(const_iterator pos, InputIterator first, InputIterator last);
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
		using node_type = ForwardListNode<T>;
		//fore->first->...->last->end
		node_type head;
		node_type tail;	
		//Using nullptr as tail is silly. 
		//Using end() from one container for operations on another is runtime_error,
		//while using nullptr will hide this error.

	};

	template<class T>
	struct ForwardListNode
	{
		T value;
		ForwardListNode* next = nullptr;

		ForwardListNode() {}
		ForwardListNode(const T& val) : value(val) {}
		ForwardListNode(const T& val, ForwardList<T>* p) : value(val), next(p) {}
		ForwardListNode(T&& val) : value(std::move(val)) {}
		ForwardListNode(T&& val, ForwardList<T>* p) : value(std::move(val)), next(p) {}
		template<typename ...Args> ForwardListNode(ForwardList<T>* p, Args && ...args) :
			value(std::forward<Args>(args)...), next(p) {}
	};

	template<typename T>
	class ForwardListIterator
	{
	public:
		using self_type = ForwardListIterator<T>;
		using value_type = ForwardListNode<T>;
		using reference = ForwardListNode<T>&;
		using pointer = ForwardListNode<T>*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;

		ForwardListIterator() {}
		ForwardListIterator(pointer _p) : p(_p) {}
		ForwardListIterator(const ForwardListIterator<T>& origin) : p(origin.p) {}
		ForwardListIterator<T>& operator=(ForwardListIterator<T>& origin) { p = origin.p; return *this; }

		ForwardListIterator<T>& operator++() { p = p->next; return *this; }
		ForwardListIterator<T> operator++(int) { ForwardListIterator ret{ *this }; ++*this; return ret; }
		bool operator==(const ForwardListIterator<T>& rhs) const { return p == rhs.p; }
		bool operator!=(const ForwardListIterator<T>& rhs) const { return p != rhs.p; }
		reference operator*() { return *p; }
		reference operator*() const { return *p; }	//Is this okay?
		pointer operator->() { return p; }
		pointer operator->() const { return p; }	//So does this?

	private:
		pointer p = nullptr;
	};

	template<typename T>
	class ForwardListConstIterator
	{
	public:
		using self_type = ForwardListConstIterator<T>;
		using value_type = ForwardListNode<T>;
		using reference = ForwardListNode<T>&;
		using pointer = ForwardListNode<T>*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;

		ForwardListConstIterator() {}
		ForwardListConstIterator(pointer _p) : p(_p) {}
		ForwardListConstIterator(const ForwardListConstIterator<T>& origin) : p(origin.p) {}
		ForwardListConstIterator(const ForwardListIterator<T>& origin) : p(origin.p) {}
		ForwardListConstIterator<T>& operator=(const ForwardListConstIterator<T>& origin) { p = origin.p; return *this; }
		ForwardListConstIterator<T>& operator=(const ForwardListIterator<T>& origin) { p = origin.p; return *this; }

		ForwardListConstIterator<T>& operator++() { p = p->next; return *this; }
		ForwardListConstIterator<T> operator++(int) { ForwardListIterator<T> ret{ *this }; ++*this; return ret; }
		bool operator==(const ForwardListConstIterator<T>& rhs) const { return p == rhs.p; }
		bool operator!=(const ForwardListConstIterator<T>& rhs) const { return p != rhs.p; }
		const reference operator*() { return *p; }
		const reference operator*() const { return *p; }	//Is this okay?
		const pointer operator->() { return p; }
		const pointer operator->() const { return p; }	//So does this?

	private:
		pointer p = nullptr;
	};

	/* Dividing Line (д├ бузе бу;)д├ (д├ бузе бу;)д├ (д├ бузе бу;)д├  */

	template<typename T>
	inline ForwardList<T>::ForwardList() noexcept 
	{
		head.next = &tail;
	}

	template<typename T>
	inline ForwardList<T>::ForwardList(size_type n)
	{
		//node_type* curr = &head;
		//for (size_t i = 0; i < n; i++)
		//{
		//	curr->next = new node_type();
		//	curr = curr->next;
		//}
		//curr->next = &tail;
		iterator curr = begin();
		for (size_t i = 0; i < n; i++)
			curr++->next = new node_type();
		curr->next = end().p;
	}

	template<typename T>
	inline ForwardList<T>::ForwardList(size_type n, const T & val)
	{
		//node_type* curr = &head;
		//for (size_t i = 0; i < n; i++)
		//{
		//	curr->next = new node_type(val);
		//	curr = curr->next;
		//}
		//curr->next = &tail;
		iterator curr = begin();
		for (size_t i = 0; i < n; i++)
			curr++->next = new node_type(val);
		curr->next = end().p;
	}

	template<typename T>
	inline ForwardList<T>::ForwardList(const_iterator first, const_iterator last)
	{
		//node_type* curr = &head;
		//while (first != last)
		//{
		//	curr->next = new node_type(*first++);
		//	curr = curr->next;
		//}
		//curr->next = &tail;
		iterator curr = begin();
		while (first != last)
			curr++->next = new node_type(*first++);
		curr->next = end().p;
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
		swap(origin);
	}

	template<typename T>
	inline ForwardList<T>::~ForwardList()
	{
		clear();
	}

	template<typename T>
	inline ForwardList<T>& ForwardList<T>::operator=(ForwardList<T> origin)
	{
		swap(origin);
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
		swap(origin);
		return *this;
	}

	template<typename T>
	inline void ForwardList<T>::assign(size_type n, const T & val)
	{
		swap(ForwardList<T>(n, val));
	}

	template<typename T>
	inline void ForwardList<T>::assign(std::initializer_list<T> list)
	{
		swap(list);
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
		for (iterator prev = before_begin(), curr = begin(); curr != end(); prev = curr++)
			delete prev.p;
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
	inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, size_type n, T & val)
	{
		for (size_t i = 0; i < n; i++)
			pos = insert_after(pos, val);
		return pos;
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, std::initializer_list<T> list)
	{
		for (const T& elem : list)
			pos = insert_after(pos, val);
		return pos;
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::erase_after(const_iterator pos)
	{
		iterator ret = pos++;
		ret->next = pos->next;
		delete pos.p;
		return ret;
	}

	template<typename T>
	inline typename ForwardList<T>::iterator ForwardList<T>::erase_after(const_iterator first, const_iterator last)
	{
		while (first->next != last.p)
			first = erase_after(first);	//Must refresh first!
		return first;
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
		iterator curr = begin();
		while (curr != end())
		{
			++cnt;
			if (cnt == n)
				curr = erase_after(curr, end());
			++curr;
		}
		for (size_t i = cnt; i < n; i++)
			insert_after(curr, n, val);
	}

	template<typename T>
	template<class InputIterator>
	inline void ForwardList<T>::assign(InputIterator first, InputIterator last)
	{
		swap(ForwardList<T>(first, last));
	}

	template<typename T>
	template<typename InputIterator>
	inline typename ForwardList<T>::iterator ForwardList<T>::insert_after(const_iterator pos, InputIterator first, InputIterator last)
	{
		while (first != last)
			pos = insert_after(pos, *first++);
		return pos;
	}

	template<typename T>
	template<typename ...Args>
	inline typename ForwardList<T>::iterator ForwardList<T>::emplace_after(const_iterator pos, Args && ...args)
	{
		return pos->next = new ForwardListNode<T>(pos->next, std::forward<Args>(args) ...);
	}

	template<typename T>
	template<typename ...Args>
	inline void ForwardList<T>::emplace_front(Args && ...args)
	{
		head.next = new ForwardListNode<T>(head.next, std::forward<Args>(args) ...);
	}

	template<typename T>
	inline void ForwardList<T>::swap(ForwardList<T>& other)
	{
		std::swap(head.next, other.head.next);
		std::swap(before_end()->next, other.before_end()->next);
	}
}