#include "AoC.h"

std::string getCommonLetters(const std::vector<std::string>& backpacks)
{
	std::string commonLetters;
	for (auto& backpack : backpacks)
	{
		bool found = false;
		for (std::size_t i = 0; i < backpack.size() / 2; i++)
		{
			for (std::size_t j = backpack.size() / 2; j < backpack.size(); j++)
				if (backpack.at(i) == backpack.at(j))
				{
					commonLetters += backpack.at(i);
					found = true;
					break;
				}
			if (found)
				break;
		}
	}
	return commonLetters;
}

std::string getCommonLettersP2(const std::vector<std::vector<std::string>>& groups)
{
	std::string commonLetters;
	for (auto& group : groups)
	{
		std::map<char, int> repeatingLetters;
		for (std::size_t i = 0; i < group.size(); i++)
		{
			std::map<char, int> currentUniqueString;
			for (std::size_t j = 0; j < group.at(i).size(); j++)
			{
				auto letter = group.at(i).at(j);
				if (currentUniqueString.find(letter) != currentUniqueString.end())
					continue;
				currentUniqueString.insert(std::make_pair(letter, 0));
				repeatingLetters.insert(std::make_pair(letter, 0));
			}
			for (auto& letter : currentUniqueString)
				repeatingLetters[letter.first] += 1;
			currentUniqueString.clear();
		}
		for (auto& letter : repeatingLetters)
			if (letter.second == 3)
				commonLetters += letter.first;
	}
	return commonLetters;
}

std::vector<std::string> getBackpacks(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> backpacks;

	backpacks.reserve(300);

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			backpacks.push_back(line);
		file.close();
	}
	return backpacks;
}

std::vector<std::vector<std::string>> distributeIntoGroups(const std::vector<std::string>& backpacks)
{
	std::vector<std::vector<std::string>> groups;

	groups.reserve(100);

	for (std::size_t i = 0; i < backpacks.size(); i += 3)
	{
		std::vector<std::string> group;

		group.reserve(3);

		group.push_back(backpacks[i]);
		group.push_back(backpacks[i + 1]);
		group.push_back(backpacks[i + 2]);
		groups.push_back(group);
	}
	return groups;
}

unsigned int calculatePriority(const std::string& commonLetters)
{
	unsigned int priority = 0;
	for (auto letter : commonLetters)
		if (std::isupper(letter))
			priority += static_cast<unsigned int>(letter) - 38;
		else
			priority += static_cast<unsigned int>(letter) - 96;
	return priority;
}

void Day3()
{
	std::vector<std::string> backpacks = getBackpacks("res/Input3.txt");
	std::string commonLetters = getCommonLetters(backpacks);
	unsigned int priority = calculatePriority(commonLetters);
	std::vector<std::vector<std::string>> groups = distributeIntoGroups(backpacks);
	std::string commonLettersP2 = getCommonLettersP2(groups);
	unsigned int priorityP2 = calculatePriority(commonLettersP2);

	std::cout << "Advent of Code 2022, Day 3" << std::endl;
	std::cout << "The sum of the priorities of item types: " << priority << std::endl;
	std::cout << "The sum of the priorities of item types P2: " << priorityP2 << std::endl;
	std::cout << std::endl;
}