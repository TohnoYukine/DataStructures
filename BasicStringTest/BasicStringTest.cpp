// BasicStringTest.cpp : Defines the entry point for the console application.
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


#include "BasicString.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "BasicStringTest.h"

using std::cin;
using std::cout;
using std::string;
namespace DS = DataStructures;

template<typename InputIterator>
void print(InputIterator begin, InputIterator end, char delim = ' ')
{
	cout << *begin++;
	while (begin != end)
		cout << delim << *begin++;
	cout << '\n';
}

template<typename T, typename Traits, template<typename, typename> typename Container>
void print(const Container<T, Traits>& container)
{
	if (!container.empty())
	{
		Container<T, Traits>::const_iterator curr = container.cbegin();
		while (curr != container.cend())
			cout << *curr++;
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
	//ConstructorTester();
	//AssignmentTester();
	//ElementAccessTester();
	//IteratorsTester();
	//CapacityTester();
	//ModifiersTester();
	//NonMemberFunctionsTester();

	//Report all memory leaks
	_CrtDumpMemoryLeaks();
	return 0;
}

void ConstructorTester()
{
	//Constructors
	//(1) Default constructor. Constructs empty string (zero size and unspecified capacity).
	DS::String str1;
	//(2) Constructs the string with count copies of character ch.
	DS::String str2(11, 'a');
	//(3) Constructs the string with a substring [pos, pos+count) of other.
	DS::String str3(str2, 2);
	DS::String str3_2(str2, 2, 5);
	//(4) Constructs the string with the first count characters of character string pointed to by s.
	DS::String str4("Hello, world!", 7);
	//(5) Constructs the string with the contents initialized with a copy of the null-terminated character string pointed to by s.
	DS::String str5("Hello, C++!");
	//(6) Constructs the string with the contents of the range [first, last).
	DS::String str6(str4.cbegin(), str4.cend());
	//(7) Copy constructor. Constructs the string with the copy of the contents of other.
	DS::String str7(str3);
	//(8) Move constructor. Constructs the string with the contents of other using move semantics.
	DS::String tempstr(str4);
	DS::String str8(std::move(tempstr));
	//(9) Constructs the string with the contents of the initializer list init.
	DS::String str9{ 'a','b','c','d' };

	print(str1);
	print(str2);
	print(str3);
	print(str3_2);
	print(str4);
	print(str5);
	print(str6);
	print(str7);
	print(tempstr);
	print(str8);
	print(str9);
}

void AssignmentTester()
{
	DS::String str("Hello, world!");

	//operator=
	//(1) Replaces the contents with a copy of str.
	DS::String str1;
	str1 = str;
	//(2) Replaces the contents with those of str using move semantics.
	DS::String tempstr(str);
	DS::String str2;
	str2 = std::move(tempstr);
	//(3) Replaces the contents with those of null-terminated character string pointed to by s.
	DS::String str3;
	str3 = "Hello, C++!";
	//(4) Replaces the contents with character ch.
	DS::String str4;
	str4 = 'A';
	//(5) Replaces the contents with those of the initializer list.
	DS::String str5;
	str5 = { 'C','+','+' };

	//assign
	//(1) Replaces the contents with count copies of character ch.
	DS::String astr1;
	astr1.assign(10, 'T');
	//(2) Replaces the contents with a copy of str.
	DS::String astr2;
	astr2.assign(str);
	//(3) Replaces the contents with a substring[pos, pos + count) of str.
	DS::String astr3;
	DS::String astr3_2;
	astr3.assign(str, 7);
	astr3_2.assign(str, 7, 5);
	//(4) Replaces the contents with those of str using move semantics.Equivalent to *this = std::move(str).
	DS::String tempastr(str);
	DS::String astr4;
	astr4.assign(std::move(tempastr));
	//(5) Replaces the contents with the first count characters of character string pointed to by s.
	DS::String astr5;
	astr5.assign("Hello,\0\0 C++!", 11);
	//(6) Replaces the contents with those of null - terminated character string pointed to by s.
	DS::String astr6;
	astr6.assign("Hello\0\0!");
	//(7) Replaces the contents with copies of the characters in the range[first, last).
	DS::String astr7;
	astr7.assign(astr3.begin(), astr3.end());
	//(8) Replaces the contents with those of the initializer list ilist.
	DS::String astr8;
	astr8.assign({ 'C','+','+' });

	print(str);
	print(str1);
	print(tempstr);
	print(str2);
	print(str3);
	print(str4);
	print(str5);

	print(astr1);
	print(astr2);
	print(astr3);
	print(astr3_2);
	print(tempastr);
	print(astr4);
	print(astr5);
	print(astr6);
	print(astr7);
	print(astr8);
}

//void ElementAccessTester()
//{
//	DS::String str{ 0,1,2,3,4,5,6,7,8,9 };
//
//	//at(size_type index)
//	try
//	{
//		for (size_t i = 0; i < 11; i++) cout << str.at(i)++ << ' ';
//	}
//	catch (const std::exception& ex)
//	{
//		cout << ex.what() << '\n';
//	}
//
//	//operator[](size_type index)
//	try
//	{
//		for (size_t i = 0; i < 11; i++) cout << str.at(i)-- << ' ';
//	}
//	catch (const std::exception& ex)
//	{
//		cout << ex.what() << '\n';
//	}
//
//	//front()
//	cout << str.front() << '\n';
//
//	//back()
//	cout << str.back() << '\n';
//
//	//data()
//	try
//	{
//		cout << str.data() << '\n';
//		for (size_t i = 0; i <= str.size(); i++)
//			cout << str.data()[i]++ << ' ';
//	}
//	catch (const std::exception& ex)
//	{
//		cout << ex.what() << '\n';
//	}
//}
//
//void IteratorsTester()
//{
//	DS::BasicString<char> str;
//	for (size_t i = 0; i < 26; i++) str.push_back(static_cast<char>('a' + i));
//	const DS::BasicString<char> cstr(str.begin(), str.end());
//
//	for (DS::BasicString<char>::iterator curr = str.begin(); curr != str.end(); ++curr)
//		cout << (*curr)-- << ' ';
//	cout << '\n';
//
//	for (DS::BasicString<char>::const_iterator curr = str.cbegin(); curr != str.cend(); ++curr)
//		cout << *curr << ' ';
//	cout << '\n';
//
//	for (DS::BasicString<char>::const_iterator curr = cstr.begin(); curr != cstr.end(); ++curr)
//		cout << *curr << ' ';
//	cout << '\n';
//
//	for (DS::BasicString<char>::const_iterator curr = cstr.cbegin(); curr != cstr.cend(); ++curr)
//		cout << *curr << ' ';
//	cout << '\n';
//
//	for (DS::BasicString<char>::reverse_iterator curr = str.rbegin(); curr != str.rend(); ++curr)
//		cout << (*curr)++ << ' ';
//	cout << '\n';
//
//	for (DS::BasicString<char>::const_reverse_iterator curr = str.crbegin(); curr != str.crend(); ++curr)
//		cout << *curr << ' ';
//	cout << '\n';
//
//	for (DS::BasicString<char>::const_reverse_iterator curr = cstr.rbegin(); curr != cstr.rend(); ++curr)
//		cout << *curr << ' ';
//	cout << '\n';
//
//	for (DS::BasicString<char>::const_reverse_iterator curr = cstr.crbegin(); curr != cstr.crend(); ++curr)
//		cout << *curr << ' ';
//	cout << '\n';
//
//	DS::BasicString<std::string> sstr{ "Hello", "World" };
//	print(sstr);
//	cout << sstr.begin()->size() << '\n';
//}
//
//void CapacityTester()
//{
//	DS::String str{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	print(str);
//	cout << std::boolalpha << str.empty() << '\n'
//		<< str.size() << '\n'
//		<< str.max_size() << '\n'
//		<< str.capacity() << '\n';
//	str.reserve(100);
//	print(str);
//	cout << std::boolalpha << str.empty() << '\n'
//		<< str.size() << '\n'
//		<< str.max_size() << '\n'
//		<< str.capacity() << '\n';
//	str.shrink_to_fit();
//	print(str);
//	cout << std::boolalpha << str.empty() << '\n'
//		<< str.size() << '\n'
//		<< str.max_size() << '\n'
//		<< str.capacity() << '\n';
//}
//
//void ModifiersTester()
//{
//	DS::String str{ 1,2,3 };
//	DS::String str2{ 1,2,3,4,5,6,7,8,9 };
//	print(str);
//
//	//clear()
//	str.clear();
//	print(str);
//
//	//insert();
//	int a = 10;
//	DS::String::iterator pos = str.insert(str.end(), a++);
//	print(str);
//	pos = str.insert(pos, a++);
//	print(str);
//	pos = str.insert(pos, std::move(a));
//	print(str);
//	pos = str.insert(pos, str2.begin(), str2.end());
//	print(str);
//	pos = str.insert(pos, { 2,2,2 });
//	print(str);
//
//	//emplace()
//	pos = str.emplace(str.cbegin() + 1, 77);
//	print(str);
//
//	//erase()
//	pos = str.erase(pos);
//	print(str);
//	pos = str.erase(pos, pos + 2);
//	print(str);
//
//	//push_back()
//	DS::BasicString<std::string> sstr{ "Hello" };
//	sstr.push_back(std::string("!"));
//	print(sstr);
//
//	//pop_back()
//	sstr.pop_back();
//	print(sstr);
//
//	//emplace_back()
//	cout << sstr.emplace_back("world") << '\n';
//	print(sstr);
//
//	//resize()
//	sstr.resize(10, "Nice");
//	print(sstr);
//	sstr.resize(4);
//	print(sstr);
//
//	//swap()
//	sstr.swap(DS::BasicString<std::string>{ "Hello, world!", "Hello, C++!" });
//	print(sstr);
//}
//
//void NonMemberFunctionsTester()
//{
//	DS::String str1{ 0,1,2,3,4,5,6,7,8,9 };
//	DS::String str2{ 0,1,2,3,4,5,6,7,8 };
//	DS::String str3{ 0,1,2,3,4,5,7,8,9 };
//	DS::String str4{ 0,1,2,3,4,5,6,7,8,9 };
//	cout << std::boolalpha
//		<< (str1 == str2) << '\n'	//False
//		<< (str1 >= str2) << '\n'	//True
//		<< (str2 > str3) << '\n'	//False
//		<< (str1 < str3) << '\n'	//True
//		<< (str1 <= str4) << '\n'	//True
//		<< (str1 != str4) << '\n';	//False
//
//	DS::swap(str1, str2);
//	DS::swap(str3, str4);
//	cout << std::boolalpha
//		<< (str1 == str2) << '\n'	//False
//		<< (str1 >= str2) << '\n'	//False
//		<< (str2 > str3) << '\n'	//False
//		<< (str1 < str3) << '\n'	//True
//		<< (str1 <= str4) << '\n'	//True
//		<< (str1 != str4) << '\n';	//True
//}
