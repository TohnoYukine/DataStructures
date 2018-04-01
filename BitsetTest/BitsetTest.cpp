// BitsetTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataStructures\Bitset.h"

namespace DS = DataStructures;

int main()
{
	DS::Bitset<100> myset;
	for (size_t i = 0; i < 10; i += 3)
		myset.set(i);
	std::cout << myset << '\n';
	return 0;
}

