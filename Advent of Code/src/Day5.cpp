#include "AoC.h"

std::vector<std::string> splitInstruction(const std::string& instruction, const std::string& delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::size_t posStart = 0;
	std::size_t posEnd = 0;
	while ((posEnd = instruction.find(delimiter, posStart)) != std::string::npos)
	{
		token = instruction.substr(posStart, posEnd - posStart);
		posStart = posEnd + delimiter.length();
		tokens.push_back(token);
	}
	tokens.push_back(instruction.substr(posStart));
	return tokens;
}

std::vector<std::stack<char>> constructStacks(const std::vector<std::string>& input)
{
	std::ptrdiff_t blankLine = -1;
	for (std::size_t i = 0; i < input.size(); i++)
		if (input.at(i).empty())
		{
			blankLine = i;
			break;
		}
	std::vector<std::stack<char>> stacks;
	const std::string& stackLabels = input.at(blankLine - 1);
	
	stacks.reserve(9);

	for (std::size_t i = 0; i < stackLabels.size(); i++)
	{
		if (stackLabels.at(i) == ' ')
			continue;
		std::stack<char> stack;
		for (std::ptrdiff_t j = blankLine - 2; j >= 0; j--)
		{
			const std::string& line = input.at(j);
			const char crate = line.at(i);
			if (crate == ' ')
				break;
			stack.push(crate);
		}
		stacks.push_back(stack);
	}
	for (std::size_t i = blankLine + 1; i < input.size(); i++)
	{
		const std::string& line = input.at(i);
		std::vector<std::string> tokens = splitInstruction(line, " ");
		int amount = std::stoi(tokens.at(1));
		int src = std::stoi(tokens.at(3)) - 1;
		int dst = std::stoi(tokens.at(5)) - 1;

		while (amount-- > 0)
		{
			char crate = stacks.at(src).top();
			stacks.at(src).pop();
			stacks.at(dst).push(crate);
		}
	}
	return stacks;
}

std::vector<std::stack<char>> constructStacksP2(const std::vector<std::string>& input)
{
	std::ptrdiff_t blankLine = -1;
	for (std::size_t i = 0; i < input.size(); i++)
		if (input.at(i).empty())
		{
			blankLine = i;
			break;
		}
	std::vector<std::stack<char>> stacks;
	const std::string& stackLabels = input.at(blankLine - 1);
	for (std::size_t i = 0; i < stackLabels.size(); i++)
	{
		if (stackLabels.at(i) == ' ')
			continue;
		std::stack<char> stack;
		for (std::ptrdiff_t j = blankLine - 2; j >= 0; j--)
		{
			const std::string& line = input.at(j);
			const char crate = line.at(i);
			if (crate == ' ')
				break;
			stack.push(crate);
		}
		stacks.push_back(stack);
	}
	for (std::size_t i = blankLine + 1; i < input.size(); i++)
	{
		const std::string& line = input.at(i);
		std::vector<std::string> tokens = splitInstruction(line, " ");
		int amount = std::stoi(tokens.at(1));
		int src = std::stoi(tokens.at(3)) - 1;
		int dst = std::stoi(tokens.at(5)) - 1;
		std::vector<char> crates;
		while (amount-- > 0)
		{
			char crate = stacks.at(src).top();
			stacks.at(src).pop();
			crates.push_back(crate);
		}
		for (std::ptrdiff_t i = crates.size() - 1; i >= 0; i--)
			stacks.at(dst).push(crates.at(i));
			
	}
	return stacks;
}

std::vector<std::string> getStacksAndInstructions(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> input;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			input.push_back(line);
		file.close();
	}
	return input;
}

std::string getTopCrates(const std::vector<std::stack<char>> stacks)
{
	std::string crates;
	for (auto& stack : stacks)
		crates += stack.top();
	return crates;
}

void Day5()
{
	std::vector<std::string> input = getStacksAndInstructions("res/Input5.txt");
	std::vector<std::stack<char>> stacks = constructStacks(input);
	std::vector<std::stack<char>> stacksP2 = constructStacksP2(input);
	std::string topCrates = getTopCrates(stacks);
	std::string topCratesP2 = getTopCrates(stacksP2);

	std::cout << "Advent of Code 2022, Day 5" << std::endl;
	std::cout << "Crates on top of each stack: " << topCrates << std::endl;
	std::cout << "Crates on top of each stack P2: " << topCratesP2 << std::endl;
	std::cout << std::endl;
}