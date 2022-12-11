#include "AoC.h"

std::vector<std::string> getProgram(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> program;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			program.push_back(line);
		file.close();
	}
	return program;
}

int getSignalStrength(const std::vector<std::string>& program)
{
	int signalStrength = 0;
	int registerValue = 1;
	std::vector<int> signals;
	for (const auto& command : program)
	{
		const std::string& instruction = command.substr(0, 4);
		if (instruction == "addx")
		{
			int value = std::stoi(command.substr(4));
			signals.push_back(registerValue);
			signals.push_back(registerValue);
			registerValue += value;
		}
		else if (instruction == "noop")
			signals.push_back(registerValue);
	}
	for (std::size_t i = 19; i <= 219; i += 40)
		signalStrength += (static_cast<int>(i) + 1) * signals.at(i);
	return signalStrength;
}

void crtDraw(const std::vector<std::string>& program)
{
	int registerValue = 1;
	std::vector<int> signals;
	for (const auto& command : program)
	{
		const std::string& instruction = command.substr(0, 4);
		if (instruction == "addx")
		{
			int value = std::stoi(command.substr(4));
			signals.push_back(registerValue);
			signals.push_back(registerValue);
			registerValue += value;
		}
		else if (instruction == "noop")
			signals.push_back(registerValue);
	}
	constexpr std::size_t w = 40, h = 6;
	std::vector<char> crt(w * h, '.');
	for (std::size_t i = 0; i < crt.size(); i++)
	{
		std::pair<std::size_t, std::size_t> pixel(i % w, i / h);
		std::size_t x = signals.at(i);
		if (x - 1 <= pixel.first && pixel.first <= x + 1)
			crt.at(i) = '#';
	}
	for (std::size_t i = 0; i < crt.size(); i++)
	{
		std::cout << crt.at(i);
		if (!((i + 1) % w))
			std::cout << std::endl;
	}
}

void Day10()
{
	std::vector<std::string> program = getProgram("res/Input10.txt");
	int signalStrength = getSignalStrength(program);

	std::cout << "Advent of Code 2022, Day 10" << std::endl;
	std::cout << "The sum of the six signal strengths: " << signalStrength << std::endl;
	std::cout << "The eight capital letters on the CRT: " << std::endl;

	crtDraw(program);

	std::cout << std::endl;
}