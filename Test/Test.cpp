// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SomeVector.h"
#include <iostream>
#include <forward_list>
#include <set>
#include <vector>

struct User 
{
	const char* name;
	const char* id;
	int dept;
};

int main() 
{
	std::vector<User> heads = 
	{
		"Ritchie D.M.", "dmr", 11271,
		"Sethi R.", "ravi", 11272,
		"Szymanski T.G.", "tgs", 11273,
		"Schr yer N.L.", "nls", 11274,
		"Schr yer N.L.", "nls", 11275,
		"Kernighan B.W.", "bwk", 11276
	};
	return 0;
}