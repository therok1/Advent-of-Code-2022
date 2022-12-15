#include "AoC.h"

typedef long long int64;

int64 magnitude(const std::pair<int64, int64>& sensor, const std::pair<int64, int64>& beacon)
{
	return std::abs(sensor.first - beacon.first) + 
		std::abs(sensor.second - beacon.second);
}

int64 tuningFrequency(const std::pair<int64, int64>& coordinate)
{
	return static_cast<int64>(4000000) * coordinate.first + coordinate.second;
}

bool withinRange(const std::pair<int64, int64>& coordinate, int64 maxCoordinates)
{
	return coordinate.first >= 0 && coordinate.first <= maxCoordinates &&
		coordinate.second >= 0 && coordinate.second <= maxCoordinates;
}

bool checkSensors(const std::map<std::pair<int64, int64>, int64>& sensors,
	const std::pair<int64, int64>& beacon)
{
	for (const auto& sensor : sensors)
		if (magnitude(sensor.first, beacon) <= sensor.second)
			return false;
	return true;
}

std::vector<int64> splitCoordinates(const std::string& coordinates)
{
	std::vector<int64> coordinateValues;
	std::string temp;
	for (std::size_t i = 0; i < coordinates.size(); i++)
	{
		const char digit = coordinates.at(i);
		if (std::isdigit(digit) || digit == '-')
			temp.push_back(digit);
		for (std::size_t j = i + 1; j < coordinates.size(); j++)
		{
			const char cDigit = coordinates.at(j);
			if (j >= coordinates.size())
				break;
			else if (std::isdigit(cDigit) || cDigit == '-')
			{
				temp.push_back(cDigit);
				i = j;
			}
			else
				break;
		}
		std::stringstream ss(temp);
		for (int64 n = 0; ss >> n; )
			coordinateValues.push_back(n);
		temp.clear();
	}
	return coordinateValues;
}

std::vector<std::string> getCoordinates(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> coordinates;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			coordinates.push_back(line);
		file.close();
	}
	return coordinates;
}

int64 parseAndGetPositionsNotContainingBeacon(const std::vector<std::string>& coordinates, int64 y)
{
	std::map<std::pair<int64, int64>, int64> sensors;
	std::map<std::pair<int64, int64>, bool> beacons;
	int64 minX = INT_MAX, maxX = INT_MIN;
	for (const auto& coordinate : coordinates)
	{
		std::vector<int64> coordinateValues = splitCoordinates(coordinate);
		std::pair<int64, int64> sensor(coordinateValues.at(0), coordinateValues.at(1));
		std::pair<int64, int64> beacon(coordinateValues.at(2), coordinateValues.at(3));
		int64 distance = magnitude(sensor, beacon);
		sensors[sensor] = distance;
		beacons[beacon] = true;
		minX = std::min(minX, sensor.first - distance);
		maxX = std::max(maxX, sensor.first + distance);
	}
	int64 positions = 0;
	for (std::ptrdiff_t i = minX; i <= maxX; i++)
		if (!checkSensors(sensors, std::make_pair(i, y)) && !beacons[std::make_pair(i, y)])
			positions++;
	return positions;
}

int64 parseAndGetTuningFrequency(const std::vector<std::string>& coordinates, int64 maxCoordinates)
{
	std::map<std::pair<int64, int64>, int64> sensors;
	std::map<std::pair<int64, int64>, bool> beacons;
	for (const auto& coordinate : coordinates)
	{
		std::vector<int64> coordinateValues = splitCoordinates(coordinate);
		std::pair<int64, int64> sensor(coordinateValues.at(0), coordinateValues.at(1));
		std::pair<int64, int64> beacon(coordinateValues.at(2), coordinateValues.at(3));
		int64 distance = magnitude(sensor, beacon);
		sensors[sensor] = distance;
		beacons[beacon] = true;
	}
	for (const auto& sensor : sensors)
	{
		std::pair<int64, int64> t(sensor.first.first, sensor.first.second - sensor.second - 1);
		std::pair<int64, int64> b(sensor.first.first, sensor.first.second + sensor.second + 1);
		std::pair<int64, int64> l(sensor.first.first - sensor.second - 1, sensor.first.second);
		std::pair<int64, int64> r(sensor.first.first + sensor.second + 1, sensor.first.second);
		while (withinRange(t, maxCoordinates) && magnitude(t, sensor.first) == sensor.second + 1)
		{
			if (checkSensors(sensors, t))
				return tuningFrequency(t);
			t.first++;
			t.second++;
		}
		while (withinRange(r, maxCoordinates) && magnitude(r, sensor.first) == sensor.second + 1)
		{
			if (checkSensors(sensors, r))
				return tuningFrequency(r);
			r.first--;
			r.second++;
		}
		while (withinRange(b, maxCoordinates) && magnitude(b, sensor.first) == sensor.second + 1)
		{
			if (checkSensors(sensors, b))
				return tuningFrequency(b);
			b.first--;
			b.second--;
		}
		while (withinRange(l, maxCoordinates) && magnitude(l, sensor.first) == sensor.second + 1)
		{
			if (checkSensors(sensors, l))
				return tuningFrequency(l);
			l.first++;
			l.second--;
		}
	}
	return 0;
}

void Day15()
{
	std::vector<std::string> coordinates = getCoordinates("res/Input15.txt");
	int64 positions = parseAndGetPositionsNotContainingBeacon(coordinates, 2000000);
	int64 tuningFrequency = parseAndGetTuningFrequency(coordinates, 4000000);

	std::cout << "Advent of Code 2022, Day 15" << std::endl;
	std::cout << "The number of positions that cannot contain a beacon at y=2000000: " << positions << std::endl;
	std::cout << "The tuning frequency of the beacon on the only possible position: " << tuningFrequency << std::endl;
	std::cout << std::endl;
}