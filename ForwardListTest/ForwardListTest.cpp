// ForwardListTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ForwardList.h"
#include <iostream>

using std::cin;
using std::cout;

template<typename InputIterator>
void print(InputIterator begin, InputIterator end, char delim = ' ')
{
	cout << *begin++;
	while (begin != end)
		cout << delim << *begin++;
	cout << '\n';
}

int main()
{
	DataStructures::ForwardList<int> ls1;
	DataStructures::ForwardList<int> ls2(10);
	DataStructures::ForwardList<int> ls3(10, 1);
	
	return 0;
}

