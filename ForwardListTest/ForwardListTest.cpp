// ForwardListTest.cpp : Defines the entry point for the console application.
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
#include <vector>
#include <iomanip>
#include <string>
#include "ForwardList.h"
#include "ForwardListTest.h"

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
	//(1) Default constructor. Constructs an empty container.
	DS::ForwardList<int> fwdls1;
	//(2) Constructs the container with count copies of elements with value value.
	DS::ForwardList<int> fwdls2(11, 3);
	//(3) Constructs the container with count default-inserted instances of T. No copies are made.
	DS::ForwardList<int> fwdls3(7);
	DS::ForwardList<int> fwdls3_2(0);
	//(4) Constructs the container with the contents of the range [first, last).
	std::vector<int> stlvec{ 0,1,2,3,4,5,6,7,8,9 };
	DS::ForwardList<int> fwdls4(stlvec.begin() + 2, stlvec.end());
	DS::ForwardList<int> fwdls4_2(++fwdls4.begin(), fwdls4.end());
	//(5) Copy constructor. Constructs the container with the copy of the contents of other.
	DS::ForwardList<int> fwdls5(fwdls3);
	//(6) Move constructor. Constructs the container with the contents of other using move semantics.
	DS::ForwardList<int> tempfwdls(fwdls4);
	DS::ForwardList<int> fwdls6(std::move(tempfwdls));
	//(7) Allocator-extended move constructor.
	//ForwardList does not use allocator.
	//(8) Constructs the container with the contents of the initializer list.
	//DS::ForwardList<int> fwdls7{ 0,1,2,3,4,5,6,7,8,9 };

	print(fwdls1);
	print(fwdls2);
	print(fwdls3);
	print(fwdls3_2);
	print(fwdls4);
	print(fwdls4_2);
	print(fwdls5);
	print(tempfwdls);
	cout << std::boolalpha
		<< (fwdls1.begin() == fwdls1.before_end()) << '\n'
		<< (fwdls1.begin() == fwdls1.end()) << '\n'
		<< (fwdls1.before_begin() == fwdls1.before_end()) << '\n';

	//print(fwdls6);
	//print(fwdls7);
}
/*
void AssignmentTester()
{
	DS::ForwardList<double> fwdls{ 0,1,2,3,4,5,6,7,8,9 };
	//(1) Copy assignment operator. Replaces the contents with a copy of the contents of other.
	DS::ForwardList<double> fwdls1{ 3,4 };
	fwdls1 = fwdls;
	//(2) Move assignment operator. Replaces the contents with those of other using move semantics.
	DS::ForwardList<double> fwdls2;
	fwdls2 = std::move(fwdls1);
	//(3) Replaces the contents with those identified by initializer list.
	DS::ForwardList<double> fwdls3;
	fwdls3 = { 1,1,1.4 };
	DS::ForwardList<int> fwdls4{ 1,2 };
	fwdls4.assign(7, 9);
	DS::ForwardList<double> fwdls5{ 1,2 };
	fwdls5.assign(fwdls4.begin() + 3, fwdls4.end());
	DS::ForwardList<double> fwdls6{ 1,2 };
	fwdls6.assign({ 7,8,9 });

	print(fwdls);
	print(fwdls1);
	print(fwdls2);
	print(fwdls3);
	print(fwdls4);
	print(fwdls5);
	print(fwdls6);
}
*/

/*
void ElementAccessTester()
{
	DS::ForwardList<int> fwdls{ 0,1,2,3,4,5,6,7,8,9 };

	//at(size_type index)
	try
	{
		for (size_t i = 0; i < 11; i++) cout << fwdls.at(i)++ << ' ';
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << '\n';
	}

	//operator[](size_type index)
	try
	{
		for (size_t i = 0; i < 11; i++) cout << fwdls.at(i)-- << ' ';
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << '\n';
	}

	//front()
	cout << fwdls.front() << '\n';

	//back()
	cout << fwdls.back() << '\n';

	//data()
	try
	{
		cout << fwdls.data() << '\n';
		for (size_t i = 0; i <= fwdls.size(); i++)
			cout << fwdls.data()[i]++ << ' ';
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << '\n';
	}
}
*/

/*
void IteratorsTester()
{
	DS::ForwardList<char> fwdls;
	for (size_t i = 0; i < 26; i++) fwdls.push_back(static_cast<char>('a' + i));
	const DS::ForwardList<char> cfwdls(fwdls.begin(), fwdls.end());

	for (DS::ForwardList<char>::iterator curr = fwdls.begin(); curr != fwdls.end(); ++curr)
		cout << (*curr)-- << ' ';
	cout << '\n';

	for (DS::ForwardList<char>::const_iterator curr = fwdls.cbegin(); curr != fwdls.cend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	for (DS::ForwardList<char>::const_iterator curr = cfwdls.begin(); curr != cfwdls.end(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	for (DS::ForwardList<char>::const_iterator curr = cfwdls.cbegin(); curr != cfwdls.cend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	for (DS::ForwardList<char>::reverse_iterator curr = fwdls.rbegin(); curr != fwdls.rend(); ++curr)
		cout << (*curr)++ << ' ';
	cout << '\n';

	for (DS::ForwardList<char>::const_reverse_iterator curr = fwdls.crbegin(); curr != fwdls.crend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	for (DS::ForwardList<char>::const_reverse_iterator curr = cfwdls.rbegin(); curr != cfwdls.rend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';

	for (DS::ForwardList<char>::const_reverse_iterator curr = cfwdls.crbegin(); curr != cfwdls.crend(); ++curr)
		cout << *curr << ' ';
	cout << '\n';
}
*/

/*
void CapacityTester()
{
	DS::ForwardList<int> fwdls{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	print(fwdls);
	cout << std::boolalpha << fwdls.empty() << '\n'
		<< fwdls.size() << '\n'
		<< fwdls.max_size() << '\n'
		<< fwdls.capacity() << '\n';
	fwdls.reserve(100);
	print(fwdls);
	cout << std::boolalpha << fwdls.empty() << '\n'
		<< fwdls.size() << '\n'
		<< fwdls.max_size() << '\n'
		<< fwdls.capacity() << '\n';
	fwdls.shrink_to_fit();
	print(fwdls);
	cout << std::boolalpha << fwdls.empty() << '\n'
		<< fwdls.size() << '\n'
		<< fwdls.max_size() << '\n'
		<< fwdls.capacity() << '\n';
}
*/

/*
void ModifiersTester()
{
	DS::ForwardList<int> fwdls{ 1,2,3 };
	DS::ForwardList<int> fwdls2{ 1,2,3,4,5,6,7,8,9 };
	print(fwdls);

	//clear()
	fwdls.clear();
	print(fwdls);

	//insert();
	int a = 10;
	DS::ForwardList<int>::iterator pos = fwdls.insert(fwdls.end(), a++);
	print(fwdls);
	pos = fwdls.insert(pos, a++);
	print(fwdls);
	pos = fwdls.insert(pos, std::move(a));
	print(fwdls);
	pos = fwdls.insert(pos, fwdls2.begin(), fwdls2.end());
	print(fwdls);
	pos = fwdls.insert(pos, { 2,2,2 });
	print(fwdls);

	//emplace()
	pos = fwdls.emplace(fwdls.cbegin() + 1, 77);
	print(fwdls);

	//erase()
	pos = fwdls.erase(pos);
	print(fwdls);
	pos = fwdls.erase(pos, pos + 2);
	print(fwdls);

	//push_back()
	DS::ForwardList<std::string> sfwdls{ "Hello" };
	sfwdls.push_back(std::string("!"));
	print(sfwdls);

	//pop_back()
	sfwdls.pop_back();
	print(sfwdls);

	//emplace_back()
	cout << sfwdls.emplace_back("world") << '\n';
	print(sfwdls);

	//resize()
	sfwdls.resize(10, "Nice");
	print(sfwdls);
	sfwdls.resize(4);
	print(sfwdls);

	//swap()
	sfwdls.swap(DS::ForwardList<std::string>{ "Hello, world!", "Hello, C++!" });
	print(sfwdls);
}
*/

void OperationsTester()
{

}

/*
void NonMemberFunctionsTester()
{
	DS::ForwardList<int> fwdls1{ 0,1,2,3,4,5,6,7,8,9 };
	DS::ForwardList<int> fwdls2{ 0,1,2,3,4,5,6,7,8 };
	DS::ForwardList<int> fwdls3{ 0,1,2,3,4,5,7,8,9 };
	DS::ForwardList<int> fwdls4{ 0,1,2,3,4,5,6,7,8,9 };
	cout << std::boolalpha
		<< (fwdls1 == fwdls2) << '\n'	//False
		<< (fwdls1 >= fwdls2) << '\n'	//True
		<< (fwdls2 > fwdls3) << '\n'	//False
		<< (fwdls1 < fwdls3) << '\n'	//True
		<< (fwdls1 <= fwdls4) << '\n'	//True
		<< (fwdls1 != fwdls4) << '\n';	//False

	DS::swap(fwdls1, fwdls2);
	DS::swap(fwdls3, fwdls4);
	cout << std::boolalpha
		<< (fwdls1 == fwdls2) << '\n'	//False
		<< (fwdls1 >= fwdls2) << '\n'	//False
		<< (fwdls2 > fwdls3) << '\n'	//False
		<< (fwdls1 < fwdls3) << '\n'	//True
		<< (fwdls1 <= fwdls4) << '\n'	//True
		<< (fwdls1 != fwdls4) << '\n';	//True
}
*/