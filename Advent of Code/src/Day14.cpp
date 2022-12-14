#include "AoC.h"

std::vector<std::string> getTraces(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> traces;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			traces.push_back(line);
		file.close();
	}
	return traces;
}

std::unordered_map<std::size_t, std::unordered_map<std::size_t, bool>>
parseTraces(const std::vector<std::string>& traces, std::ptrdiff_t& mY)
{
	std::unordered_map<std::size_t, std::unordered_map<std::size_t, bool>> grid;
	for (const auto& trace : traces)
	{
		std::ptrdiff_t i = 0, pX = 0, pY = 0;
		while (i < trace.size())
		{
			while (!std::isdigit(trace[i]))
				i++;
			std::ptrdiff_t x = 0, y = 0;
			while (std::isdigit(trace[i]))
			{
				x = 10 * x + trace.at(i) - '0';
				i++;
			}
			i++;
			while (std::isdigit(trace[i]))
			{
				y = 10 * y + trace.at(i) - '0';
				i++;
			}
			grid[x][y] = true;
			if (pX && pY)
				if (pX == x)
					for (std::size_t i = std::min(pY, y); i <= std::max(pY, y); i++)
						grid[x][i] = true;
				else
					for (std::size_t i = std::min(pX, x); i <= std::max(pX, x); i++)
						grid[i][y] = true;
			pX = x;
			pY = y;
			mY = std::max(y, mY);
		}
	}
	return grid;
}

std::size_t getSandUnits(
	std::unordered_map<std::size_t, std::unordered_map<std::size_t, bool>>& grid,
	std::ptrdiff_t mY)
{
	std::size_t x = 500, y = 0;
	std::size_t grains = 0;
	while (grid.find(x) != grid.end())
	{
		if (y == mY)
			break;
		if (grid[x].find(y + 1) == grid[x].end())
		{
			y++;
			continue;
		}
		if (grid.find(x - 1) == grid.end())
			break;
		if (grid[x - 1].find(y + 1) == grid[x - 1].end())
		{
			x--;
			y++;
			continue;
		}
		if (grid.find(x + 1) == grid.end())
			break;
		if (grid[x + 1].find(y + 1) == grid[x + 1].end())
		{
			x++;
			y++;
			continue;
		}
		grid[x][y] = true;
		grains++;
		x = 500;
		y = 0;
	}
	return grains;
}

std::size_t getSandUnitsP2(
	std::unordered_map<std::size_t, std::unordered_map<std::size_t, bool>>& grid,
	std::ptrdiff_t mY)
{
	std::size_t x = 500, y = 0;
	std::size_t grains = 0;
	mY += 2;
	while (y != mY) {
		if (y == mY - 1) {
			grid[x][y] = true;
			grains++;
			x = 500;
			y = 0;
			continue;
		}
		if (grid[x].find(y + 1) == grid[x].end()) 
		{
			y++;
			continue;
		}
		if (grid.find(x - 1) == grid.end()) 
		{
			x--;
			y++;
			continue;
		}
		if (grid[x - 1].find(y + 1) == grid[x - 1].end()) 
		{
			x--;
			y++;
			continue;
		}
		if (grid.find(x + 1) == grid.end()) 
		{
			x++;
			y++;
			continue;
		}
		if (grid[x + 1].find(y + 1) == grid[x + 1].end()) 
		{
			x++;
			y++;
			continue;
		}
		grid[x][y] = true;
		grains++;
		if (x == 500 && y == 0)
			break;
		x = 500;
		y = 0;
	}
	return grains;
}

void Day14()
{
	std::vector<std::string> traces = getTraces("res/Input14.txt");
	std::ptrdiff_t mY = PTRDIFF_MIN;
	std::ptrdiff_t mYP2 = PTRDIFF_MIN;
	std::unordered_map<std::size_t, std::unordered_map<std::size_t, bool>> grid = parseTraces(traces, mY);
	std::unordered_map<std::size_t, std::unordered_map<std::size_t, bool>> gridP2 = parseTraces(traces, mYP2);
	std::size_t grains = getSandUnits(grid, mY);
	std::size_t grainsP2 = getSandUnitsP2(gridP2, mYP2);

	std::cout << "Advent of Code 2022, Day 14" << std::endl;
	std::cout << "Units of sand needed before sand starts flowing into the abyss: " << grains << std::endl;
	std::cout << "Units of sand coming to rest: " << grainsP2 << std::endl;
	std::cout << std::endl;
}