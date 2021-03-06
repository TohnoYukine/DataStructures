// UtilityTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Utility\StdIOStream.h"
#include "UtilityTest.h"

int main()
try
{
	StdioWrapperFundamentalTypeTest();
	StdioWrapperCStringTest();
	//std::cout << Stdin.FormattingPlaceholder<char[20]>() << '\n';
	//std::cout << Stdin.FormattingPlaceholder<double>() << '\n';

	return 0;
}
catch (const std::exception& ex)
{
	std::cerr << ex.what() << '\n';
}

void StdioWrapperFundamentalTypeTest()
{
	char c;
	int i;
	long l;
	short s;
	float f;
	double d;
	Stdin
		>> c
		>> i
		>> l
		>> s
		>> f
		>> d;
	std::cout
		<< c << '\n'
		<< i << '\n'
		<< l << '\n'
		<< s << '\n'
		<< f << '\n'
		<< d << '\n';
	Stdout
		<< c << '\n'
		<< i << '\n'
		<< l << '\n'
		<< s << '\n'
		<< f << '\n'
		<< d << '\n';
}

void StdioWrapperCStringTest()
{
	char cstr[20];
	char* cstr2 = new char[50];
	Stdin("%19s", 19) >> cstr;
	Stdin("%19s", 19) >> cstr2;
	std::cout << cstr << '\n' << cstr2 << '\n';
	Stdout
		<< cstr << '\n';
	Stdout
		<< cstr2 << '\n';
	delete cstr2;
}
