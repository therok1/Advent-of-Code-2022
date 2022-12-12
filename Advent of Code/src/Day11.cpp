#include "AoC.h"

typedef long long int64;

struct Monkey
{
	std::vector<int64> StartingItems;
	char Operation;
	std::string Value;
	int DivisibleBy = 1;
	unsigned int TrueID = 0, FalseID = 0;
	std::function<int64(int64)> PerformOperation;
	int64 TotalInspects = 0;
	int64 MaxWorry = 0;

	void Inspect(std::map<unsigned int, Monkey>& monkeys)
	{
		for (auto worryLevel : StartingItems)
		{
			TotalInspects++;
			int64 newWorryLevel = PerformOperation(worryLevel) / 3;
			unsigned int target = (newWorryLevel % DivisibleBy == 0) ? TrueID : FalseID;
			monkeys.at(target).StartingItems.push_back(newWorryLevel);
		}
		StartingItems.clear();
	}

	void InspectP2(std::map<unsigned int, Monkey>& monkeys)
	{
		for (auto worryLevel : StartingItems)
		{
			TotalInspects++;
			int64 newWorryLevel = PerformOperation(worryLevel) % MaxWorry;
			unsigned int target = (newWorryLevel % DivisibleBy == 0) ? TrueID : FalseID;
			monkeys.at(target).StartingItems.push_back(newWorryLevel);
		}
		StartingItems.clear();
	}
};

std::vector<std::string> splitWorryLevels(const std::string& worryLevels, const std::string& delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::size_t posStart = 0;
	std::size_t posEnd = 0;
	while ((posEnd = worryLevels.find(delimiter, posStart)) != std::string::npos)
	{
		token = worryLevels.substr(posStart, posEnd - posStart);
		posStart = posEnd + delimiter.length();
		tokens.push_back(token);
	}
	tokens.push_back(worryLevels.substr(posStart));
	return tokens;
}

std::vector<std::string> getMonkeyInput(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> monkeys;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			monkeys.push_back(line);
		file.close();
	}
	return monkeys;
}

std::map<unsigned int, Monkey> distributeMonkeys(const std::vector<std::string>& monkeyInput)
{
	std::map<unsigned int, Monkey> monkeys;
	std::vector<int> divisors;
	for (std::size_t i = 0; i < monkeyInput.size(); i += 7)
	{
		Monkey monkey;
		std::vector<std::string> worryLevelsStr = splitWorryLevels(monkeyInput.at(i + 1).substr(18), ", ");
		std::vector<int64> worryLevels(worryLevelsStr.size());
		std::transform(
			worryLevelsStr.begin(),
			worryLevelsStr.end(),
			worryLevels.begin(),
			[](std::string worryLevel)
			{
				return std::stoi(worryLevel);
			}
		);
		monkey.StartingItems = worryLevels;
		monkey.Operation = monkeyInput.at(i + 2).substr(23, 1).at(0);
		monkey.Value = monkeyInput.at(i + 2).substr(25);
		monkey.DivisibleBy = std::stoi(monkeyInput.at(i + 3).substr(21));
		monkey.TrueID = std::stoi(monkeyInput.at(i + 4).substr(29));
		monkey.FalseID = std::stoi(monkeyInput.at(i + 5).substr(30));
		if (monkey.Value == "old")
			monkey.PerformOperation = (monkey.Operation == '*') ? 
				std::function<int64(int64)>{ [](int64 worryLevel) { return worryLevel * worryLevel; } } :
				std::function<int64(int64)>{ [](int64 worryLevel) { return worryLevel + worryLevel; } };
		else
		{
			int value = std::stoi(monkey.Value);
			monkey.PerformOperation = (monkey.Operation == '*') ?
				std::function<int64(int64)>{ [value](int64 worryLevel) { return worryLevel * value; } } :
				std::function<int64(int64)>{ [value](int64 worryLevel) { return worryLevel + value; } };
		}
		divisors.push_back(monkey.DivisibleBy);
		monkeys.emplace(std::stoi(monkeyInput.at(i).substr(7, 1)), monkey);
	}
	int64 maxWorry = std::accumulate(
		divisors.begin(), 
		divisors.end(), 
		1l, 
		[](int64 total, int value)
		{
			return total * value;
		}
	);
	for (auto& monkey : monkeys)
		monkey.second.MaxWorry = maxWorry;
	return monkeys;
}

int64 getMonkeyBusiness(std::map<unsigned int, Monkey>& monkeys, std::size_t rounds)
{
	int64 totalInspects = 0;
	for (std::size_t i = 0; i < rounds; i++)
		for (auto& monkey : monkeys)
			rounds == 20 ? monkey.second.Inspect(monkeys) : monkey.second.InspectP2(monkeys);
	std::vector<Monkey> monkeysSorted;
	for (const auto& monkey : monkeys)
		monkeysSorted.emplace_back(monkey.second);
	std::sort(
		monkeysSorted.begin(), 
		monkeysSorted.end(),
		[](const Monkey& rhs, const Monkey& lhs)
		{
			return rhs.TotalInspects > lhs.TotalInspects;
		}
	);
	totalInspects = monkeysSorted.at(0).TotalInspects * monkeysSorted.at(1).TotalInspects;
	return totalInspects;
}

void Day11()
{
	std::vector<std::string> monkeyInput = getMonkeyInput("res/Input11.txt");
	std::map<unsigned int, Monkey> monkeys = distributeMonkeys(monkeyInput);
	std::map<unsigned int, Monkey> monkeysP2 = distributeMonkeys(monkeyInput);
	int64 monkeyBusiness20 = getMonkeyBusiness(monkeys, 20);
	int64 monkeyBusiness10000 = getMonkeyBusiness(monkeysP2, 10000);

	std::cout << "Advent of Code 2022, Day 11" << std::endl;
	std::cout << "The level of monkey business over 20 rounds: " << monkeyBusiness20 << std::endl;
	std::cout << "The level of monkey business over 10000 rounds: " << monkeyBusiness10000 << std::endl;
	std::cout << std::endl;
}