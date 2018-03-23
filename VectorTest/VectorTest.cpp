// VectorTest.cpp : Defines the entry point for the console application.
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


#include "Vector.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "VectorTest.h"
#include "Algorithm\Algorithm.h"

using std::cin;
using std::cout;
using std::string;
using DataStructures::Print;
namespace DS = DataStructures;

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
	IteratorsTester();
	CapacityTester();
	ModifiersTester();
	NonMemberFunctionsTester();

	//Report all memory leaks
	_CrtDumpMemoryLeaks();
	return 0;
}

void ConstructorTester()
{
	std::cout << "Running " << __FUNCTION__ << "()\n";
	//Constructors
	//(1) Default constructor. Constructs an empty container.
	DS::Vector<int> vec1;
	DS::Vector<string> svec1;
	//(2) Constructs the container with count copies of elements with value value.
	DS::Vector<int> vec2(11, 3);
	DS::Vector<string> svec2(11, "Hello");
	//(3) Constructs the container with count default-inserted instances of T. No copies are made.
	DS::Vector<int> vec3(7);
	DS::Vector<int> vec3_2(0);
	DS::Vector<string> svec3(11);
	DS::Vector<string> svec3_2(0);
	//(4) Constructs the container with the contents of the range [first, last).
	std::vector<int> stlvec{ 0,1,2,3,4,5,6,7,8,9 };
	DS::Vector<int> vec4(stlvec.begin() + 2, stlvec.end());
	DS::Vector<int> vec4_2(vec4.begin() + 1, vec4.end());
	std::vector<string> stlsvec{ "a","b","c","d","e" };
	DS::Vector<string> svec4(stlsvec.begin() + 2, stlsvec.end());
	DS::Vector<string> svec4_2(svec4.begin() + 1, svec4.end());
	//(5) Copy constructor. Constructs the container with the copy of the contents of other.
	DS::Vector<int> vec5(vec3);
	DS::Vector<string> svec5(svec3);
	//(6) Move constructor. Constructs the container with the contents of other using move semantics.
	DS::Vector<int> tempvec(vec4);
	DS::Vector<int> vec6(std::move(tempvec));
	DS::Vector<string> tempsvec(svec4);
	DS::Vector<string> svec6(std::move(tempsvec));
	//(7) Allocator-extended move constructor.
	//Not tested yet.
	//(8) Constructs the container with the contents of the initializer list.
	DS::Vector<int> vec7{ 0,1,2,3,4,5,6,7,8,9 };
	DS::Vector<string> svec7{ "a","b","c","d","e" };

	Print(vec1);	//{}
	Print(vec2);	//{3 3 3 3 3 3 3 3 3 3 3}
	Print(vec3);	//{0 0 0 0 0 0 0}
	Print(vec3_2);	//{}
	Print(vec4);	//{2 3 4 5 6 7 8 9}
	Print(vec4_2);	//{3 4 5 6 7 8 9}
	Print(vec5);	//{0 0 0 0 0 0 0}
	Print(tempvec);	//{}
	Print(vec6);	//{2 3 4 5 6 7 8 9}
	Print(vec7);	//{0 1 2 3 4 5 6 7 8 9}

	Print(svec1);	//{}
	Print(svec2);	//{Hello Hello Hello Hello Hello Hello Hello Hello Hello Hello Hello}
	Print(svec3);	//{"" "" "" "" "" "" "" "" "" "" ""}
	Print(svec3_2);	//{}
	Print(svec4);	//{}
	Print(svec4_2);	//{c d e}
	Print(svec5);	//{d e}
	Print(tempsvec);//{}
	Print(svec6);	//{c d e}
	Print(svec7);	//{a b c d e}
}

void AssignmentTester()
{
	std::cout << "Running " << __FUNCTION__ << "()\n";
	DS::Vector<double> vec{ 0,1,2,3,4,5,6,7,8,9 };
	//(1) Copy assignment operator. Replaces the contents with a copy of the contents of other.
	DS::Vector<double> vec1{ 3,4 };
	vec1 = vec;
	//(2) Move assignment operator. Replaces the contents with those of other using move semantics.
	DS::Vector<double> vec2;
	vec2 = std::move(vec1);
	//(3) Replaces the contents with those identified by initializer list.
	DS::Vector<double> vec3;
	vec3 = { 1,1,1.4 };
	DS::Vector<int> vec4{ 1,2 };
	vec4.assign(7, 9);
	DS::Vector<double> vec5{ 1,2 };
	vec5.assign(vec4.begin() + 3, vec4.end());
	DS::Vector<double> vec6{ 1,2 };
	vec6.assign({ 7,8,9 });

	Print(vec);		//{0 1 2 3 4 5 6 7 8 9}
	Print(vec1);	//{}
	Print(vec2);	//{0 1 2 3 4 5 6 7 8 9}
	Print(vec3);	//{1 1 1.4}
	Print(vec4);	//{9 9 9 9 9 9 9}
	Print(vec5);	//{9 9 9 9}
	Print(vec6);	//{7 8 9}
}

void ElementAccessTester()
{
	std::cout << "Running " << __FUNCTION__ << "()\n";
	DS::Vector<int> vec{ 0,1,2,3,4,5,6,7,8,9 };

	//at(size_type index)
	try
	{
		for (size_t i = 0; i < 11; i++) cout << vec.at(i)++ << ' ';
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << '\n';
	}

	//operator[](size_type index)
	try
	{
		for (size_t i = 0; i < 11; i++) cout << vec.at(i)-- << ' ';
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << '\n';
	}

	//front()
	cout << vec.front() << '\n';

	//back()
	cout << vec.back() << '\n';

	//data()
	try
	{
		cout << vec.data() << '\n';
		for (size_t i = 0; i <= vec.size(); i++)
			cout << vec.data()[i]++ << ' ';
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << '\n';
	}
}

void IteratorsTester()
{
	std::cout << "Running " << __FUNCTION__ << "()\n";
	DS::Vector<char> vec;
	for (size_t i = 0; i < 26; i++) vec.push_back(static_cast<char>('a' + i));
	const DS::Vector<char> cvec(vec.begin(), vec.end());
	
	//{a b c d e f g h i j k l m n o p q r s t u v w x y z}
	for (DS::Vector<char>::iterator curr = vec.begin(); curr != vec.end(); ++curr)
		cout << (*curr)-- << ' ';
	cout << '\n';

	//{` a b c d e f g h i j k l m n o p q r s t u v w x y}
	for (DS::Vector<char>::const_iterator curr = vec.cbegin(); curr != vec.cend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	//{a b c d e f g h i j k l m n o p q r s t u v w x y z}
	for (DS::Vector<char>::const_iterator curr = cvec.begin(); curr != cvec.end(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	//{a b c d e f g h i j k l m n o p q r s t u v w x y z}
	for (DS::Vector<char>::const_iterator curr = cvec.cbegin(); curr != cvec.cend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	//{y x w v u t s r q p o n m l k j i h g f e d c b a `}
	for (DS::Vector<char>::reverse_iterator curr = vec.rbegin(); curr != vec.rend(); ++curr)
		cout << (*curr)++ << ' ';
	cout << '\n';

	//{z y x w v u t s r q p o n m l k j i h g f e d c b a}
	for (DS::Vector<char>::const_reverse_iterator curr = vec.crbegin(); curr != vec.crend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	//{z y x w v u t s r q p o n m l k j i h g f e d c b a}
	for (DS::Vector<char>::const_reverse_iterator curr = cvec.rbegin(); curr != cvec.rend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	//{z y x w v u t s r q p o n m l k j i h g f e d c b a}
	for (DS::Vector<char>::const_reverse_iterator curr = cvec.crbegin(); curr != cvec.crend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	//Hello World, 5
	DS::Vector<std::string> svec{ "Hello", "World" };
	Print(svec);
	cout << svec.begin()->size() << '\n';
}

void CapacityTester()
{
	std::cout << "Running " << __FUNCTION__ << "()\n";
	DS::Vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Print(vec);
	cout << std::boolalpha << vec.empty() << '\n'	//false
		<< vec.size() << '\n'						//10
		<< vec.max_size() << '\n'					//4294967295
		<< vec.capacity() << '\n';					//10
	vec.reserve(100);
	Print(vec);
	cout << std::boolalpha << vec.empty() << '\n'	//false
		<< vec.size() << '\n'						//10
		<< vec.max_size() << '\n'					//4294967295
		<< vec.capacity() << '\n';					//100
	vec.shrink_to_fit();
	Print(vec);
	cout << std::boolalpha << vec.empty() << '\n'	//false
		<< vec.size() << '\n'						//10
		<< vec.max_size() << '\n'					//4294967295
		<< vec.capacity() << '\n';					//10
}

void ModifiersTester()
{
	std::cout << "Running " << __FUNCTION__ << "()\n";
	DS::Vector<int> vec{ 1,2,3 };
	DS::Vector<int> vec2{ 1,2,3,4,5,6,7,8,9 };
	Print(vec);	//{1 2 3}

	//clear()
	vec.clear();
	Print(vec);	//{}

	//insert();
	int a = 10;
	DS::Vector<int>::iterator pos = vec.insert(vec.end(), a++);
	Print(vec);	//{10}
	pos = vec.insert(pos, a++);
	Print(vec);	//{11 10}
	pos = vec.insert(pos, std::move(a));
	Print(vec);	//{12 11 10}
	pos = vec.insert(pos, vec2.begin(), vec2.end());
	Print(vec);	//{1 2 3 4 5 6 7 8 9 12 11 10}
	pos = vec.insert(pos, { 2,2,2 });
	Print(vec);	//{2 2 2 1 2 3 4 5 6 7 8 9 12 11 10}

	//emplace()
	pos = vec.emplace(vec.cbegin() + 1, 77);
	Print(vec);	//{2 77 2 2 1 2 3 4 5 6 7 8 9 12 11 10}

	//erase()
	pos = vec.erase(pos);
	Print(vec);	//{2 2 2 1 2 3 4 5 6 7 8 9 12 11 10}
	pos = vec.erase(pos, pos + 2);
	Print(vec);	//{2 1 2 3 4 5 6 7 8 9 12 11 10}

	//push_back()
	DS::Vector<std::string> svec{ "Hello" };
	svec.push_back(std::string("!"));
	Print(svec);	//{Hello !}

	//pop_back()
	svec.pop_back();
	Print(svec);	//{Hello}

	//emplace_back()
	cout << svec.emplace_back("world") << '\n';
	Print(svec);	//{Hello world}

	//resize()
	svec.resize(10, "Nice");
	Print(svec);	//{Hello world Nice Nice Nice Nice Nice Nice Nice Nice}
	svec.resize(4);
	Print(svec);	//{Hello world Nice Nice}

	//swap()
	svec.swap(DS::Vector<std::string>{ "Hello, world!", "Hello, C++!" });
	Print(svec);	//{Hello, world! Hello, C++!}
}

void NonMemberFunctionsTester()
{
	std::cout << "Running " << __FUNCTION__ << "()\n";
	DS::Vector<int> vec1{ 0,1,2,3,4,5,6,7,8,9 };
	DS::Vector<int> vec2{ 0,1,2,3,4,5,6,7,8 };
	DS::Vector<int> vec3{ 0,1,2,3,4,5,7,8,9 };
	DS::Vector<int> vec4{ 0,1,2,3,4,5,6,7,8,9 };
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
