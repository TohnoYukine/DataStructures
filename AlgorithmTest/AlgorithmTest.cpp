// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Algorithm.h"
#include "AlgorithmTest.h"
#include <vector>
#include <iostream>
#include <stack>

int main()
{
	RotateTest();
	return 0;
}

void RotateTest()
{
	std::vector<int> ivec{ 0,1,2,3,4,5,6,7,8,9 };
	std::vector<int> ivec2(ivec);
	Print(ivec);
	Rotate(ivec.begin(), ivec.begin() + 4, ivec.end() - 2);
	Rotate(ivec2.begin(), ivec2.begin() + 6, ivec2.end());
	Print(ivec);
	Print(ivec2);
}

