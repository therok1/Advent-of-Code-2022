#include "AoC.h"

std::vector<std::vector<std::string>> distributeElves(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::vector<std::string>> elves;
	std::vector<std::string> elf;

	elves.reserve(250);
	elf.reserve(15);

	if (file.is_open())
	{
		std::size_t currentElf = 0;
		std::string line;
		while (std::getline(file, line))
		{
			if ((currentElf + 1) > elves.size())
				elves.push_back(elf);
			if (!line.empty())
				elves.at(currentElf).push_back(line);
			else
				currentElf++;
		}
		file.close();
	}
	return elves;
}

std::vector<unsigned int> sumElvesCalories(const std::vector<std::vector<std::string>>& elves)
{
	std::vector<unsigned int> elvesCalories;
	for (auto& elf : elves)
	{
		unsigned int sum = 0;
		for (auto& calories : elf)
			sum += std::stoi(calories);
		elvesCalories.push_back(sum);
	}
	return elvesCalories;
}

unsigned int findElfWithMostCalories(const std::vector<unsigned int>& elvesCalories)
{
	return *std::max_element(elvesCalories.begin(), elvesCalories.end());
}

unsigned int findThreeElvesWithMostCalories(std::vector<unsigned int> elvesCalories)
{
	unsigned int sum = 0;
	std::sort(elvesCalories.begin(), elvesCalories.end());
	for (std::size_t i = elvesCalories.size() - 1; i > elvesCalories.size() - 4; i--)
	{
		auto element = elvesCalories.at(i);
		sum += element;
	}
		
	return sum;
}

void Day1()
{
	std::vector<std::vector<std::string>> elves = distributeElves("res/Input1.txt");
	std::vector<unsigned int> elvesCalories = sumElvesCalories(elves);
	unsigned int mostCalories = findElfWithMostCalories(elvesCalories);
	unsigned int topThreeCalories = findThreeElvesWithMostCalories(elvesCalories);

	std::cout << "Advent of Code 2022, Day 1" << std::endl;
	std::cout << "Most calories an elf is carrying: " << mostCalories << std::endl;
	std::cout << "Calories sum of top three elves: " << topThreeCalories << std::endl;
	std::cout << std::endl;
}