#include "AoC.h"

struct AssignmentPair
{
	int L1, L2;
	int R1, R2;

	AssignmentPair(int l1, int l2, int r1, int r2)
		: L1(l1), L2(l2), R1(r1), R2(r2)
	{

	}
};

std::vector<AssignmentPair> parseSections(const std::vector<std::string>& sections)
{
	std::vector<AssignmentPair> sectionAssignments;
	for (auto& section : sections)
	{
		std::string leftToken = section.substr(0, section.find(","));
		std::string rightToken = section.substr(section.find(",") + 1, section.size());
		std::vector<int> numbers;
		std::stringstream left(leftToken), right(rightToken);

		numbers.reserve(4);

		for (int i = 0; left >> i; )
			numbers.push_back(std::abs(i));
		for (int i = 0; right >> i; )
			numbers.push_back(std::abs(i));
		sectionAssignments.push_back(AssignmentPair(numbers[0], numbers[1], numbers[2], numbers[3]));
	}
	return sectionAssignments;
}

std::vector<std::string> getSections(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> sections;

	sections.reserve(1000);

	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			sections.push_back(line);
		file.close();
	}
	return sections;
}

bool contains(const AssignmentPair& a)
{
	return ((a.L1 <= a.R1) && (a.L2 >= a.R2)) || ((a.R1 <= a.L1) && (a.R2 >= a.L2));
}

bool overlaps(const AssignmentPair& a)
{
	return (((a.L1 <= a.R1) && (a.L2 >= a.R1)) || ((a.L1 <= a.R2) && (a.L1 >= a.R2))) 
		|| (((a.R1 <= a.L1) && (a.R2 >= a.L1)) || ((a.R1 <= a.L2) && (a.R1 >= a.L2)));
}

unsigned int countContainedSections(const std::vector<AssignmentPair>& sectionAssignments)
{
	unsigned int count = 0;
	for (auto& section : sectionAssignments)
		if (contains(section))
			count++;
	return count;
}

unsigned int countOverlapedSections(const std::vector<AssignmentPair>& sectionAssignments)
{
	unsigned int count = 0;
	for (auto& section : sectionAssignments)
		if (overlaps(section))
			count++;
	return count;
}

void Day4()
{
	std::vector<std::string> sections = getSections("res/Input4.txt");
	std::vector<AssignmentPair> sectionAssignments = parseSections(sections);
	unsigned int containedSections = countContainedSections(sectionAssignments);
	unsigned int overlapedSections = countOverlapedSections(sectionAssignments);

	std::cout << "Advent of Code 2022, Day 4" << std::endl;
	std::cout << "Number of pairs where first range fully contains the other: " << containedSections << std::endl;
	std::cout << "Number of pairs where first range overlaps the other: " << overlapedSections << std::endl;
	std::cout << std::endl;
}