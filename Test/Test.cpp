// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "SomeVector.h"
#include <iostream>
#include <forward_list>
#include <set>
#include <vector>

//constexpr inline unsigned long long fib1(size_t n) { return n <= 1 ? 1 : n * fib1(n - 1); }
unsigned long long fib2(size_t n){ return n <= 1 ? 1 : n * fib2(n - 1); }

int main() 
{
	//int a = fib1(30);
	int b = fib2(30);
	//std::cout << a << '\n';
	std::cout << b << '\n';
	return 0;
}