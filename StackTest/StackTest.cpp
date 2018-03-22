// StackTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <iostream>
#include <deque>
#include <iomanip>
#include <string>
#include <stack>
#include "Stack.h"
#include "StackTest.h"

using std::cin;
using std::cout;
namespace DS = DataStructures;

template<typename InputIterator>
void print(InputIterator begin, InputIterator end, char delim = ' ')
{
	cout << *begin++;
	while (begin != end)
		cout << delim << *begin++;
	cout << '\n';
}

template<typename T, template<typename> typename Container>
void print(const Container<T>& container)
{
	if (!container.empty())
	{
		Container<T>::const_iterator curr = container.cbegin();
		cout << *curr++;
		while (curr != container.cend())
			cout << ' ' << *curr++;
	}
	cout << '\n';
}

template<typename T>
void print(const DS::Stack<T>& s)
{
	DS::Stack<T> s_copy(s);
	if (!s_copy.empty())
	{
		cout << s_copy.top();
		s_copy.pop();
		while (!s_copy.empty())
		{
			cout << ' ' << s_copy.top();
			s_copy.pop();
		}
	}
	cout << '\n';
}

int main()
{
	//Send all memory leak reports to STDOUT
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);

	//Testers here
	ConstructorTester();
	AssignmentTester();
	ElementAccessTester();
	CapacityTester();
	ModifiersTester();
	NonMemberFunctionsTester();

	//Report all memory leaks
	_CrtDumpMemoryLeaks();
	return 0;
}

void ConstructorTester()
{
	DS::Vector<int> deq{ 1,2,3,4,5,6,7,8,9 };
	
	DS::Stack<int> s1(deq);
	DS::Stack<int, DS::Vector<int>> s5(s1);
	DS::Stack<int> s2({ 1,2,3,4 });
	DS::Stack<int> s3(s2);
	DS::Stack<int> s4(DS::Stack<int>({1, 2, 3, 4, 5, 6}));

	print(s1);
	print(s2);
	print(s3);
	print(s4);
	print(s5);
}

void AssignmentTester()
{
	DS::Stack<int> s({ 1,2,3,4 });

	DS::Stack<int> s1;
	s1 = s;
	DS::Stack<int> s2;
	s2 = DS::Stack<int>({ 1,2,3,4,5 });

	print(s1);
	print(s2);
}

void ElementAccessTester()
{
	DS::Stack<int> s({ 1,2,3,4 });
	std::cout << s.top() << '\n';
}

void CapacityTester()
{
	DS::Stack<int> s1({ 1,2,3,4 });
	DS::Stack<int> s2;
	print(s1);
	std::cout << s1.empty() << '\n' << s1.size() << '\n';
	print(s2);
	std::cout << s2.empty() << '\n' << s2.size() << '\n';
}

void ModifiersTester()
{
	DS::Stack<int> s1({ 1,2,3,4 });
	s1.push(5);
	cout << s1.emplace(6) << '\n';
	s1.push(7);
	s1.pop();

	DS::Stack<int> s2({ 1,2,3 });
	s1.swap(s2);
	print(s1);
	print(s2);
}

void NonMemberFunctionsTester()
{
	DS::Stack<int> vec1({ 0,1,2,3,4,5,6,7,8,9 });
	DS::Stack<int> vec2({ 0,1,2,3,4,5,6,7,8 });
	DS::Stack<int> vec3({ 0,1,2,3,4,5,7,8,9 });
	DS::Stack<int> vec4({ 0,1,2,3,4,5,6,7,8,9 });
	cout << std::boolalpha
		<< (vec1 == vec2) << '\n'	//False
		<< (vec1 >= vec2) << '\n'	//True
		<< (vec2 > vec3) << '\n'	//False
		<< (vec1 < vec3) << '\n'	//True
		<< (vec1 <= vec4) << '\n'	//True
		<< (vec1 != vec4) << '\n';	//False

	DS::swap(vec1, vec2);
	DS::swap(vec3, vec4);
	cout << std::boolalpha
		<< (vec1 == vec2) << '\n'	//False
		<< (vec1 >= vec2) << '\n'	//False
		<< (vec2 > vec3) << '\n'	//False
		<< (vec1 < vec3) << '\n'	//True
		<< (vec1 <= vec4) << '\n'	//True
		<< (vec1 != vec4) << '\n';	//True
}


