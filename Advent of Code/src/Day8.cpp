#include "AoC.h"

std::vector<std::string> getTreeGrid(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> grid;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			grid.push_back(line);
		file.close();
	}
	return grid;
}

std::size_t countVisibleTrees(const std::vector<std::string>& treeGrid)
{
	std::size_t visibleTrees = treeGrid.size() * 2 + (treeGrid.at(0).size() - 2) * 2;
	for (std::size_t y = 1; y < treeGrid.size() - 1; y++)
		for (std::size_t x = 1; x < treeGrid.at(y).size() - 1; x++)
		{
			char tree = treeGrid.at(x).at(y);
			bool left = true;
			for (std::ptrdiff_t i = x - 1; i >= 0; i--)
				if (treeGrid.at(i).at(y) >= tree)
				{
					left = false;
					break;
				}
			bool right = true;
			for (std::size_t i = x + 1; i < treeGrid.at(y).size(); i++)
				if (treeGrid.at(i).at(y) >= tree)
				{
					right = false;
					break;
				}
			bool top = true;
			for (std::ptrdiff_t i = y - 1; i >= 0; i--)
				if (treeGrid.at(x).at(i) >= tree)
				{
					top = false;
					break;
				}
			bool bottom = true;
			for (std::size_t i = y + 1; i < treeGrid.size(); i++)
				if (treeGrid.at(x).at(i) >= tree)
				{
					bottom = false;
					break;
				}
			if (left || right || top || bottom)
				visibleTrees++;
		}
	return visibleTrees;
}

std::size_t getBestScenicScore(const std::vector<std::string>& treeGrid)
{
	std::vector<std::vector<int>> scenicScoresGrid;
	scenicScoresGrid.resize(treeGrid.size(), std::vector<int>(treeGrid.at(0).size()));
	for (std::size_t y = 1; y < treeGrid.size() - 1; y++)
		for (std::size_t x = 1; x < treeGrid.at(y).size() - 1; x++)
		{
			char tree = treeGrid.at(x).at(y);
			std::size_t left = 0;
			for (std::ptrdiff_t i = x - 1; i >= 0; i--)
			{
				left++;
				if (treeGrid.at(i).at(y) >= tree)
					break;
			}
			std::size_t right = 0;
			for (std::size_t i = x + 1; i < treeGrid.at(y).size(); i++)
			{
				right++;
				if (treeGrid.at(i).at(y) >= tree)
					break;
			}
			std::size_t top = 0;
			for (std::ptrdiff_t i = y - 1; i >= 0; i--)
			{
				top++;
				if (treeGrid.at(x).at(i) >= tree)
					break;
			}
			std::size_t bottom = 0;
			for (std::size_t i = y + 1; i < treeGrid.size(); i++)
			{
				bottom++;
				if (treeGrid.at(x).at(i) >= tree)
					break;
			}
			scenicScoresGrid.at(x).at(y) = left * right * top * bottom;
		}
	std::vector<int> scenicScores1D;
	for (std::size_t i = 0; i < scenicScoresGrid.size(); i++)
		scenicScores1D.insert(scenicScores1D.end(), scenicScoresGrid.at(i).begin(), scenicScoresGrid.at(i).end());
	return *std::max_element(scenicScores1D.begin(), scenicScores1D.end());
}

void Day8()
{
	std::vector<std::string> treeGrid = getTreeGrid("res/Input8.txt");
	std::size_t visibleTrees = countVisibleTrees(treeGrid);
	std::size_t bestScenicScore = getBestScenicScore(treeGrid);

	std::cout << "Advent of Code 2022, Day 8" << std::endl;
	std::cout << "The amount of visible trees from outside the grid: " << visibleTrees << std::endl;
	std::cout << "The best scenic score of a tree house: " << bestScenicScore << std::endl;
	std::cout << std::endl;
}