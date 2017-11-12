#pragma once
#include <deque>
#include "Vector.h"

namespace DataStructures
{
	template<typename T, typename Container = Vector<T>>
	class Stack
	{
	public:
		using container_type	= Container;
		using value_type		= typename Container::value_type;
		using reference			= typename Container::reference;
		using const_reference	= typename Container::const_reference;
		using size_type			= typename Container::size_type;

		//Constructor, Destructor and Assignment
		explicit Stack(const Container& cont);
		explicit Stack(Container&& cont = Container());
		Stack(const Stack& origin);
		Stack(Stack && origin);
		~Stack();

		Stack<T, Container>& operator=(const Stack& origin);
		Stack<T, Container>& operator=(Stack&& origin);

		//Element access
		reference top();
		const_reference top() const;

		//Capacity
		bool empty() const;
		size_type size() const;

		//Modifiers
		void push(const value_type& value);
		void push(value_type&& value);
		template <typename ... Args> reference emplace(Args&& ... args);
		void pop();
		void swap(Stack& other) noexcept;

		//Non-Member Functions
		template<typename T, typename Container> friend bool operator==(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);
		template<typename T, typename Container> friend bool operator!=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);
		template<typename T, typename Container> friend bool operator<(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);
		template<typename T, typename Container> friend bool operator<=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);
		template<typename T, typename Container> friend bool operator>(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);
		template<typename T, typename Container> friend bool operator>=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs);
		template<typename T, typename Container> friend void swap(Stack<T, Container>& lhs, Stack<T, Container>& rhs);

	private:
		Container C;
	};

	/* Dividing Line (д├ бузе бу;)д├ (д├ бузе бу;)д├ (д├ бузе бу;)д├  */

	template<typename T, typename Container>
	inline Stack<T, Container>::Stack(const Container & cont) : C(cont)
	{
	}

	template<typename T, typename Container>
	inline Stack<T, Container>::Stack(Container && cont) : C(std::move(cont))
	{
	}

	template<typename T, typename Container>
	inline Stack<T, Container>::Stack(const Stack & origin) : C(origin.C)
	{
	}

	template<typename T, typename Container>
	inline Stack<T, Container>::Stack(Stack&& origin) : C(std::move(origin.C))
	{
	}

	template<typename T, typename Container>
	inline Stack<T, Container>::~Stack()
	{
	}

	template<typename T, typename Container>
	inline Stack<T, Container>& Stack<T, Container>::operator=(const Stack& origin)
	{
		swap(Stack(origin));
		return *this;
	}

	template<typename T, typename Container>
	inline Stack<T, Container>& Stack<T, Container>::operator=(Stack && origin)
	{
		swap(origin);
		return *this;
	}

	template<typename T, typename Container>
	inline typename Stack<T, Container>::reference Stack<T, Container>::top()
	{
		return C.back();
	}

	template<typename T, typename Container>
	inline typename Stack<T, Container>::const_reference Stack<T, Container>::top() const
	{
		return C.back();
	}

	template<typename T, typename Container>
	inline bool Stack<T, Container>::empty() const
	{
		return C.empty();
	}

	template<typename T, typename Container>
	inline typename Stack<T, Container>::size_type Stack<T, Container>::size() const
	{
		return C.size();
	}

	template<typename T, typename Container>
	inline void Stack<T, Container>::push(const value_type & value)
	{
		C.push_back(value);
	}

	template<typename T, typename Container>
	inline void Stack<T, Container>::push(value_type && value)
	{
		C.push_back(std::move(value));
	}

	template<typename T, typename Container>
	inline void Stack<T, Container>::pop()
	{
		C.pop_back();
	}

	template<typename T, typename Container>
	inline void Stack<T, Container>::swap(Stack & other) noexcept
	{
		std::swap(C, other.C);
	}

	template<typename T, typename Container>
	template<typename ...Args>
	inline typename Stack<T, Container>::reference Stack<T, Container>::emplace(Args && ...args)
	{
		return C.emplace_back(std::forward<Args>(args) ... );
	}

	template<typename T, typename Container>
	bool operator==(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return lhs.C == rhs.C;
	}

	template<typename T, typename Container>
	bool operator!=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T, typename Container>
	bool operator<(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return lhs.C < rhs.C;
	}

	template<typename T, typename Container>
	bool operator<=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return  lhs.C <= rhs.C;
	}

	template<typename T, typename Container>
	bool operator>(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs <= rhs);
	}

	template<typename T, typename Container>
	bool operator>=(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs)
	{
		return !(lhs < rhs);
	}

	template<typename T, typename Container>
	void swap(Stack<T, Container>& lhs, Stack<T, Container>& rhs)
	{
		lhs.swap(rhs);
	}
}