#pragma once
#include "Vector.h"
#include <iostream>
#include <type_traits>
#include <initializer_list>

namespace DataStructures
{
	struct ExtentList	//Discribe extents of dimensions for MultiArray
	{
		std::vector<size_t> dimensions;
		ExtentList() = default;
		template<typename Iterator, typename SFINAE = std::enable_if_t<std::_Is_iterator_v<Iterator>>>
		ExtentList(Iterator begin, Iterator end) : dimensions(begin, end) {}
		//operator[] used to initialize the extents
		ExtentList& operator[](size_t n) { dimensions.push_back(n); return *this; }
		ExtentList after_front() const { return ExtentList(++dimensions.cbegin(), dimensions.cend()); }
		//at() used to access extents
		size_t at(size_t n) const { return dimensions.at(n); }
	};

	static ExtentList Extents;

	template<
		typename ElemType,													//Underlying Type
		size_t Dimension,													//Dimension of MultiArray
		typename ElementAllocator = std::allocator<ElemType>,				//Allocator for elements
		template<typename, typename> typename ContainerType = std::vector,	//Underlying container type
		template<typename> typename ContainerAllocator = std::allocator>	//Allocator for container
	class MultiArray
	{
		//Necessary for contructor with ExtentList
		friend class MultiArray<ElemType, Dimension + 1U, ElementAllocator, ContainerType, ContainerAllocator>;

		using value_type = typename
			std::conditional_t<
			Dimension == 1U, 
			ElemType,
			MultiArray<ElemType, Dimension - 1U, ElementAllocator, ContainerType, ContainerAllocator>>;
		using allocator_type = typename
			std::conditional_t<
			Dimension == 1U,
			ElementAllocator,
			ContainerAllocator<value_type>>;
		ContainerType<value_type, allocator_type> data;


	public:
		MultiArray() = default;
		MultiArray(size_t n, const value_type& val) : data(n, val) {}

		template<typename SFINAE = std::enable_if_t<(Dimension == 1U)>>
			MultiArray(ExtentList extents, const ElemType& elem) : data(extents.at(0), elem) {}
		template<typename SFINAE = std::enable_if_t<(Dimension >= 2U)>, typename SFINAE2 = SFINAE>
			MultiArray(ExtentList extents, const ElemType& elem) : data(extents.at(0), value_type(extents.after_front(), elem)) {}

		MultiArray(std::initializer_list<value_type> ilist) : data(ilist) {}
		

		template<typename ... SizeType>
		MultiArray(size_t N, SizeType... args) : data(N, value_type(args...)) {}

		value_type& operator[](size_t n) { return data[n]; }
		void push_back(const value_type& elem) { data.push_back(elem); }
	};
}