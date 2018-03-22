#pragma once
#include "Vector.h"
#include <iostream>
#include <type_traits>
#include <initializer_list>

template<typename ElemType, size_t Dimension, template<typename> typename ContainerType = DataStructures::Vector>
class MultiArray
{
	using value_type = typename std::conditional<Dimension == 1U, ElemType, MultiArray<ElemType, Dimension - 1U, ContainerType>>::type;
	ContainerType<value_type> data;

public:
	MultiArray() = default;
	MultiArray(const std::initializer_list<value_type>& ilist) : data(ilist) {}

	template<typename ... SizeType>
	MultiArray(size_t N, SizeType... args) : data(N, value_type(args...)) {}

	value_type& operator[](size_t n) { return data[n]; }
	void push_back(const value_type& elem) { data.push_back(elem); }
};