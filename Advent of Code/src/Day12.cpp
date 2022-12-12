#include "AoC.h"

std::vector<std::string> getGrid(const std::string& filepath)
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

bool available(int row, int column, int y, int x)
{
	return !(row >= y || column >= x || row < 0 || column < 0);
}

int findShortestPath(std::vector<std::string> grid, int part)
{
	std::size_t y = grid.size();
	std::size_t x = grid.at(0).size();
	std::pair<std::size_t, std::size_t> end;
	for (std::size_t i = 0; i < y; i++)
		for (std::size_t j = 0; j < x; j++)
			if (grid.at(i).at(j) == 'E')
			{
				end = std::make_pair(i, j);
				grid.at(i).at(j) = 'z';
			}
	std::queue<std::pair<std::size_t, std::pair<std::size_t, std::size_t>>> queue;
	std::vector<std::vector<bool>> visited(y, std::vector<bool>(x, false));
	visited.at(end.first).at(end.second) = true;
	queue.push(std::make_pair(0, end));
	while (!queue.empty())
	{
		int distance = queue.front().first;
		std::size_t row = queue.front().second.first;
		std::size_t column = queue.front().second.second;
		queue.pop();
		if (part == 1)
		{
			if (grid.at(row).at(column) == 'S')
				return distance;
		}
		else if (part == 2)
		{
			if (grid.at(row).at(column) == 'a')
				return distance;
		}
			
		std::array<std::size_t, 4> dx = { 1, -1, 0, 0 };
		std::array<std::size_t, 4> dy = { 0, 0, 1, -1 };
		for (std::size_t i = 0; i < 4; i++)
			if (available(row + dx.at(i), column + dy.at(i), y, x) && !visited.at(row + dx.at(i)).at(column + dy.at(i)))
			{
				char previous = grid.at(row + dx.at(i)).at(column + dy.at(i)) == 'S' ? 'a' : grid.at(row + dx.at(i)).at(column + dy.at(i));
				if (grid.at(row).at(column) - previous <= 1)
				{
					visited.at(row + dx.at(i)).at(column + dy.at(i)) = true;
					queue.push(std::make_pair(distance + 1, std::make_pair(row + dx.at(i), column + dy.at(i))));
				}
			}
	}
	return 0;
}

void Day12()
{
	std::vector<std::string> grid = getGrid("res/Input12.txt");
	int shortestPath = findShortestPath(grid, 1);
	int shortestPathP2 = findShortestPath(grid, 2);

	std::cout << "Advent of Code 2022, Day 12" << std::endl;
	std::cout << "The fewest steps required to move to the position with the best signal: " << shortestPath << std::endl;
	std::cout << "The fewest steps required to move to the position with the best signal P2: " << shortestPathP2 << std::endl;
	std::cout << std::endl;
}