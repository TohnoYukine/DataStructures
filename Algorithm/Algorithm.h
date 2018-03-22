#pragma once
#include <algorithm>
#include <iostream>
#include <utility>
#include <iterator>
#include <vector>
#include <stack>

namespace DataStructures
{
	//Print Elements in [begin, end), delimited by delim, ended by '\n'.
	template<typename InputIterator>
	void Print(InputIterator begin, InputIterator end, char delim = ' ')
	{
		if (begin != end)
			std::cout << *begin++;
		while (begin != end)
			std::cout << delim << *begin++;
		std::cout << '\n';
	}

	//Print Elements in [cont.cbegin(), cont.cend()), delimited by delim, ended by '\n'.
	template<typename Container>
	void Print(const Container& cont, char delim = ' ')
	{
		Print(cont.cbegin(), cont.cend());
	}


	//Perform a left rotation on the range of elements
	//[first, end) gives the range of elements, middle points to the element becoming the first one after rotation
	//Returns an iterator to the original first element
	template<typename ForwardIterator>
	inline ForwardIterator Rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator end)
	{
		ForwardIterator curr = middle;
		while (curr != end && first != middle)
			std::swap(*first++, *curr++);
		return
			first == middle ?
			curr == end ?
			first :
			Rotate(first, curr, end) :
			Rotate(first, middle, end);
	}


	//template<typename ForwardIterator, typename std::enable_if<std::iterator_traits<ForwardIterator>::iterator_category == std::forward_iterator_tag, void>>
	//inline std::pair<ForwardIterator, ForwardIterator> EqualRange(ForwardIterator first, ForwardIterator end)
	//{
	//	//Fibnacci Counter
	//	struct
	//	{
	//		std::vector<size_t> data;
	//		Fib() : data{ 1,1 };
	//		void gen() { data.push_back(data[data.size() - 2] + data[data.size() - 1]); }
	//		size_t pop{ size_t ret = data.back(); data.pop_back(); return ret; }
	//		size_t top{ return data.back(); }
	//	} counter;

	//	ForwardIterator curr{ first };

	//}
}
