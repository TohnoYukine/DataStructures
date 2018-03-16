// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SomeVector.h"
#include <iostream>
#include <forward_list>
#include <set>

template<typename InputIterator>
void print(InputIterator begin, InputIterator end, char delim = ' ')
{
	std::cout << *begin++;
	while (begin != end)
		std::cout << delim << *begin++;
	std::cout << '\n';
}

int main() 
{
	//int a = 3, b = 2;
	//int *pa = &a, *pb = &b;
	//std::cout << *pa << *pb << a << b << '\n';
	//std::swap(pa, pb);
	//std::cout << *pa << *pb << a << b << '\n';
	//lni::vector<int> vec{ 1,2,3 };
	//std::forward_list<int> ls{ 1,2,3 };
	//auto iter = ++++ls.begin();
	//ls.erase_after(iter);
	//std::set<int, bool(*)(const int&, const int&)> m_songs({ 2,3,4,5,1,6 }, [](const int& a, const int& b) {return a > b;});
	//std::cout << *++m_songs.find(3) << '\n';
	//print(m_songs.begin(), m_songs.end());
	char a[100];
	scanf("%s", &a);
	printf("%s", a);
	return 0;
}