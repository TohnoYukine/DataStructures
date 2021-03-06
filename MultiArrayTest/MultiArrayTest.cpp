// MultiArrayTest.cpp : Defines the entry point for the console application.
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
#include "Algorithm\Algorithm.h"
#include "DataStructures\MultiArray.h"
#include "MultiArrayTest.h"

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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Testers here
	ConstructorTester();

	//Report all memory leaks
	_CrtDumpMemoryLeaks();
	return 0;
}

void ConstructorTester()
{
	DS::MultiArray<int, 2> matrix_2d
	{
		{ 1,2,3 },
		{ 4,5,6 },
		{ 7,8,9 }
	};
	for (size_t i = 0; i != 3; ++i)
		for (size_t j = 0; j != 3; ++j)
			std::cout << matrix_2d[i][j] << ' ';

	//DS::MultiArray<int, 3> matrix_3d(DS::Extents[3][4][5], 7);
	//for (size_t i = 0; i != 3; ++i)
	//	for (size_t j = 0; j != 4; ++j)
	//		for (size_t k = 0; k != 5; ++k)
	//			std::cout << matrix_3d[3][4][5];

	DS::MultiArray<int, 3> matrix_3d(DS::Extents[10][10][10], 0);
	size_t sum = 0;
	for (size_t i = 0; i != DS::Extents.at(0); ++i)
		for (size_t j = 0; j != DS::Extents.at(1); ++j)
			for (size_t k = 0; k != DS::Extents.at(2); ++k)
				sum += (matrix_3d[i][j][k] = i * 100 + j * 10 + k);
	std::cout << sum << '\n' << matrix_3d[9][9][9] << '\n';
}
