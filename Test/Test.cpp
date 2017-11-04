// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <forward_list>
#include "SomeVector.h"

int main() 
{
	int a = 3, b = 2;
	int *pa = &a, *pb = &b;
	std::cout << *pa << *pb << a << b << '\n';
	std::swap(pa, pb);
	std::cout << *pa << *pb << a << b << '\n';
	lni::vector<int> vec{ 1,2,3 };
	std::forward_list<int> ls{ 1,2,3 };
	auto iter = ++++ls.begin();
	ls.erase_after(iter);
	return 0;
}