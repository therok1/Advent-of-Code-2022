#include "AoC.h"

std::string getSignal(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::string signal;
	if (file.is_open())
	{
		std::getline(file, signal);
		file.close();
	}
	return signal;
}

std::size_t getFirstMarker(const std::string& signal, std::size_t desiredPacketSize)
{
	std::size_t packetSize = desiredPacketSize;
	std::ptrdiff_t firstMarker = -1;
	for (std::size_t i = 0; i < signal.size() - packetSize + 1; i++)
	{
		std::string packet = signal.substr(i, packetSize);
		std::sort(packet.begin(), packet.end());
		std::string::iterator last = std::unique(packet.begin(), packet.end());
		packet.erase(last, packet.end());
		if (packet.size() == packetSize)
		{
			firstMarker = i + packetSize;
			break;
		}
	}
	return firstMarker;
}

void Day6()
{
	std::string signal = getSignal("res/Input6.txt");
	std::size_t firstPacketMarker = getFirstMarker(signal, 4);
	std::size_t firstMessageMarker = getFirstMarker(signal, 14);

	std::cout << "Advent of Code 2022, Day 6" << std::endl;
	std::cout << "The amount of characters processed before the first start-of-packet marker: " << firstPacketMarker << std::endl;
	std::cout << "The amount of characters processed before the first start-of-message marker: " << firstMessageMarker << std::endl;
	std::cout << std::endl;
}