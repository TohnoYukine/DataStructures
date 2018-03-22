#pragma once

#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <utility>
#include <chrono>
#include <tuple>
#include <iomanip>

namespace Profiler
{
	//Helper funtion
	//Returns average and sample standard deviation of the dataset
	std::tuple<double, double> calc_statistics(const std::vector<double>& vec)
	{
		double average = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
		double deviation = sqrt(std::accumulate(vec.begin(), vec.end(), 0.0, [=](double a, double b) {return a + pow(b - average, 2); }) / (vec.size() - 1));
		return std::make_tuple(average, deviation);
	}

	//Takes in a function and arguments for the function
	//Run the function f for n times. If n is 1, the time is calculated. If n is more than 1, average time and deviation is calculated.
	//You should not run f for 0 times.
	template<typename Func, typename... Args>
	void profile(size_t n, Func f, Args... args)
	{
		auto get_duration = [&]()
		{
			auto t1 = std::chrono::high_resolution_clock::now();
			f(args...);
			auto t2 = std::chrono::high_resolution_clock::now();
			return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		};

		if (n == 0) throw std::runtime_error{ "You have to run the function for at least once!" };
		else if (n == 1)
		{
			std::cout << "Duration:\t" << get_duration() << '\n';
		}
		else
		{
			std::vector<double> logs;
			for (size_t i = 0; i < n; i++)
			{
				std::cout << "Runs: " << i << '\t';
				auto result = get_duration();
				std::cout << "Duration: " << result << "\n";
				logs.push_back(result);
			}
			auto result = calc_statistics(logs);
			std::cout << "Duration:\t"
				<< std::setprecision(5)
				<< std::get<0>(result) << "\t+\t"
				<< std::get<1>(result) << '\t'
				<< "Error:\t"
				<< std::get<1>(result) / std::get<0>(result) << '\n';
		}
	}
}