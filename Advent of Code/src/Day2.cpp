#include "AoC.h"

std::pair<char, char> splitScores(const std::string& round)
{
	return std::make_pair(round.at(0), round.at(2));
}

std::vector<std::pair<char, char>> getScores(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::pair<char, char>> rounds;

	rounds.reserve(2500);

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			rounds.push_back(splitScores(line));
		file.close();
	}
	return rounds;
}

unsigned int calculateScore(const std::vector<std::pair<char, char>>& rounds, 
	const std::map<std::pair<char, char>, unsigned int>& outcomeScores, 
	const std::map<char, unsigned int>& shapeScores)
{
	unsigned int score = 0;
	for (auto& round : rounds)
	{
		score += outcomeScores.at(round) + shapeScores.at(round.second);
	}
	return score;
}

unsigned int calculateScoreP2(const std::vector<std::pair<char, char>>& rounds, 
	const std::map<std::pair<char, char>, unsigned int>& outcomeScores, 
	const std::map<std::pair<char, char>, char>& outcomeShapes,
	const std::map<char, unsigned int>& shapeScores)
{
	unsigned int score = 0;
	for (auto& round : rounds)
	{
		char shape = outcomeShapes.at(round);
		score += outcomeScores.at(std::make_pair(round.first, shape)) + shapeScores.at(shape);
	}
	return score;
}

void Day2()
{
	std::map<std::pair<char, char>, unsigned int> outcomeScores = {
		{ splitScores("A X"), 3 },
		{ splitScores("A Y"), 6 },
		{ splitScores("A Z"), 0 },
		{ splitScores("B X"), 0 },
		{ splitScores("B Y"), 3 },
		{ splitScores("B Z"), 6 },
		{ splitScores("C X"), 6 },
		{ splitScores("C Y"), 0 },
		{ splitScores("C Z"), 3 }
	};
	std::map<std::pair<char, char>, char> outcomeShapes = {
		{ splitScores("A X"), 'Z'},
		{ splitScores("A Y"), 'X' },
		{ splitScores("A Z"), 'Y' },
		{ splitScores("B X"), 'X' },
		{ splitScores("B Y"), 'Y' },
		{ splitScores("B Z"), 'Z' },
		{ splitScores("C X"), 'Y' },
		{ splitScores("C Y"), 'Z' },
		{ splitScores("C Z"), 'X' }
	};
	std::map<char, unsigned int> shapeScores = {
		{ 'X', 1 },
		{ 'Y', 2 },
		{ 'Z', 3 }
	};

	std::vector<std::pair<char, char>> scores = getScores("res/Input2.txt");
	unsigned int totalScore = calculateScore(scores, outcomeScores, shapeScores);
	unsigned int totalScoreP2 = calculateScoreP2(scores, outcomeScores, outcomeShapes, shapeScores);

	std::cout << "Advent of Code 2022, Day 2" << std::endl;
	std::cout << "Your total score: " << totalScore << std::endl;
	std::cout << "Your total score P2: " << totalScoreP2 << std::endl;
	std::cout << std::endl;
}