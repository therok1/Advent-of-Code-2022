#include "AoC.h"

struct Point
{
	int X = 0, Y = 0;

	Point operator-(const Point& p) const
	{
		Point temp;
		temp.X = X - p.X;
		temp.Y = Y - p.Y;
		return temp;
	}
	std::size_t operator()(const Point& p) const noexcept
	{
		std::size_t hash = p.X + 10 * p.Y;
		return hash;
	}
	auto operator<=>(const Point&) const = default;
};

namespace std
{
	template<> struct hash<Point>
	{
		std::size_t operator()(const Point& p) const noexcept
		{
			return p(p);
		}
	};
}

std::vector<std::string> getMotionMoves(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> motionMoves;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			motionMoves.push_back(line);
		file.close();
	}
	return motionMoves;
}

Point getTailPosition(const Point& head, const Point& tail)
{
	Point magnitude = head - tail;
	Point temp;
	if (std::abs(magnitude.X) <= 1 && std::abs(magnitude.Y) <= 1)
		return tail;
	if (head.Y == tail.Y)
	{
		temp.X = (head.X > tail.X) ? head.X - 1 : head.X + 1;
		temp.Y = tail.Y;
	}
	else if (head.X == tail.X)
	{
		temp.X = tail.X;
		temp.Y = (head.Y > tail.Y) ? head.Y - 1 : head.Y + 1;
	}
	else
	{
		temp.X = (head.X > tail.X) ? tail.X + 1 : tail.X - 1;
		temp.Y = (head.Y > tail.Y) ? tail.Y + 1 : tail.Y - 1;
	}
	return temp;
}

std::unordered_set<Point> performMovesWith2Knots(const std::vector<std::string>& motionMoves)
{
	Point head;
	Point tail;
	std::unordered_set<Point> visited;
	for (const auto& move : motionMoves)
	{
		char direction = move.at(0);
		int moves = std::stoi(move.substr(2));
		while (moves-- > 0)
		{
			if (direction == 'U')
				head.Y--;
			else if (direction == 'D')
				head.Y++;
			else if (direction == 'L')
				head.X--;
			else if (direction == 'R')
				head.X++;
			tail = getTailPosition(head, tail);
			visited.insert(tail);
		}
	}
	return visited;
}

std::unordered_set<Point> performMovesWith10Knots(const std::vector<std::string>& motionMoves)
{
	std::array<Point, 10> knots;
	Point& head = knots.at(0);
	Point& tail = knots.at(knots.size() - 1);
	std::unordered_set<Point> visited;
	for (const auto& move : motionMoves)
	{
		char direction = move.at(0);
		int moves = std::stoi(move.substr(2));
		while (moves-- > 0)
		{
			if (direction == 'U')
				head.Y--;
			else if (direction == 'D')
				head.Y++;
			else if (direction == 'L')
				head.X--;
			else if (direction == 'R')
				head.X++;
			for (std::size_t current = 0, next = 1; next < knots.size(); current++, next++)
				knots.at(next) = getTailPosition(knots.at(current), knots.at(next));
			visited.insert(tail);
		}
	}
	return visited;
}

inline std::size_t countVisitedPositions(const std::unordered_set<Point>& visited)
{
	return visited.size();
}

void Day9()
{
	std::vector<std::string> motionMoves = getMotionMoves("res/Input9.txt");
	std::unordered_set<Point> visitedPositions2K = performMovesWith2Knots(motionMoves);
	std::unordered_set<Point> visitedPositions10K = performMovesWith10Knots(motionMoves);
	std::size_t count2K = countVisitedPositions(visitedPositions2K);
	std::size_t count10K = countVisitedPositions(visitedPositions10K);

	std::cout << "Advent of Code 2022, Day 9" << std::endl;
	std::cout << "The amount of positions the tail of the rope with 2 knots has visited at least once: " << count2K << std::endl;
	std::cout << "The amount of positions the tail of the rope with 10 knots has visited at least once: " << count10K << std::endl;
	std::cout << std::endl;
}