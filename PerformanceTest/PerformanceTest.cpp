// PerformanceTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Profiler.h"
#include "Utility\StdIOStream.h"

char path[] = R"(C:\Users\TohnoYukine\Documents\Visual Studio 2017\Projects\C++ Exercise\DataStructures\x64\Release\Data001.txt)";
int main(int argc, char** argv)
{
	{
		FILE* file = fopen(path, "r");
		std::ifstream ifile(path);
		if (!file) std::cerr << "Fail to open file with fopen()!\n";
		else fclose(file);
		if (!ifile) std::cerr << "Fail to open file with ifstream!\n";
		if (!file || !ifile) return 0;
	}
	auto ifstream_test = [&]()
	{
		double d;
		std::ifstream ifile(path);
		while (ifile >> d);
	};

	auto InStream_test = [&]()
	{
		double d;
		InStream ifile(fopen(path, "r"));
		while (ifile >> d);
	};

	auto fscanf_s_test = [&]()
	{
		double d;
		FILE* file = fopen(path, "r");
		while (fscanf_s(file, "%lf", &d) > 0);
		fclose(file);
	};

	argc = 3;
	if (argc == 1) return 0;
	if (argc == 2)
	{
		Profiler::profile(1, ifstream_test);
		Profiler::profile(1, InStream_test);
		Profiler::profile(1, fscanf_s_test);
	}
	if (argc == 3)
	{
		size_t cnt = 10;
		Profiler::profile(cnt, ifstream_test);
		Profiler::profile(cnt, InStream_test);
		Profiler::profile(cnt, fscanf_s_test);
	}
    return 0;
}

