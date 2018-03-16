#pragma once
#include "Vector.h"
#include <iostream>
#include <type_traits>
#include <initializer_list>

template<typename ElemType, size_t Dimension, template<typename> typename ContainerType = DataStructures::Vector>
class MultiArray
{
	using SliceType = typename std::conditional<Dimension == 1U, ElemType, MultiArray<ElemType, Dimension - 1U, ContainerType>>::type;
	ContainerType<SliceType> data;

public:
	MultiArray() = default;
	MultiArray(const std::initializer_list<SliceType>& ilist) : data(ilist) {}

	template<typename ... SizeType>
	MultiArray(size_t N, SizeType... args) : data(N, SliceType(args...)) {}

	SliceType& operator[](size_t n) { return data[n]; }
	void push_back(const SliceType& elem) { data.push_back(elem); }
};