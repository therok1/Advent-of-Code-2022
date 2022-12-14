#include <chrono>

#include "AoC.h"

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	Day1();
	Day2();
	Day3();
	Day4();
	Day5();
	Day6();
	Day7();
	Day8();
	Day9();
	Day10();
	Day11();
	Day12();
	Day13();
	Day14();
	Day15();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Execution time: " << duration.count() << "us" << std::endl;

	return 0;
}