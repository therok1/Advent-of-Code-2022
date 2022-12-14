#include "AoC.h"

enum class EntryType
{
	INT, LIST
};

struct Entry
{
	EntryType Type = EntryType::INT;
	std::size_t Value = 0;
	std::vector<Entry> Values;

	Entry()
		: Type(EntryType::INT), Value(0)
	{

	}

	Entry(EntryType type)
		: Type(type)
	{

	}

	Entry(EntryType type, std::size_t value)
		: Type(type), Value(value)
	{

	}

	bool operator<=(const Entry& e) const
	{
		return Compare(*this, e) <= 0;
	}

	bool operator>=(const Entry& e) const
	{
		return Compare(*this, e) >= 0;
	}

	bool operator==(const Entry& e) const
	{
		return Compare(*this, e) == 0;
	}

	bool operator<(const Entry& e) const
	{
		return Compare(*this, e) < 0;
	}

	bool operator>(const Entry& e) const
	{
		return Compare(*this, e) > 0;
	}

	static std::ptrdiff_t CompareList(const Entry& lhs, const Entry& rhs)
	{
		std::size_t minSize = std::min(lhs.Values.size(), rhs.Values.size());
		for (std::size_t i = 0; i < minSize; i++)
		{
			std::ptrdiff_t result = Compare(lhs.Values.at(i), rhs.Values.at(i));
			if (result)
				return result;
		}
		return lhs.Values.size() - rhs.Values.size();
	}

	static std::ptrdiff_t Compare(const Entry& lhs, const Entry& rhs)
	{
		if (lhs.Type == EntryType::INT && rhs.Type == EntryType::INT)
			return lhs.Value - rhs.Value;
		if (lhs.Type == EntryType::INT)
		{
			Entry replacement(EntryType::LIST);
			replacement.Values.emplace_back(EntryType::INT, lhs.Value);
			return CompareList(replacement, rhs);
		}
		if (rhs.Type == EntryType::INT)
		{
			Entry replacement(EntryType::LIST);
			replacement.Values.emplace_back(EntryType::INT, rhs.Value);
			return CompareList(lhs, replacement);
		}
		return CompareList(lhs, rhs);
	}
};

std::vector<std::string> getPackets(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> packets;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			packets.push_back(line);
		file.close();
	}
	return packets;
}

Entry parse(const std::string& packet, std::size_t& offset)
{
	Entry result;
	if (packet.at(offset) != '[')
	{
		result.Type = EntryType::INT;
		std::size_t comma = packet.find(",", offset + 1);
		std::size_t bracket = packet.find("]", offset + 1);
		std::size_t end = std::min(comma, bracket);
		result.Value = static_cast<std::size_t>(std::stoi(packet.substr(offset, end - offset)));
		offset = end;
		return result;
	}
	result.Type = EntryType::LIST;
	if (packet.at(offset + 1) == ']')
	{
		offset += 2;
		return result;
	}
	while (packet.at(offset) != ']')
		result.Values.emplace_back(parse(packet, ++offset));
	offset++;
	return result;
}

Entry parse(const std::string& packet)
{
	std::size_t offset = 0;
	return parse(packet, offset);
}

std::size_t sumIndices(const std::vector<std::string>& packets)
{
	std::size_t index = 1;
	std::size_t sum = 0;
	for (std::size_t i = 0; i < packets.size(); i += 3)
	{
		const Entry packet1 = parse(packets.at(i));
		const Entry packet2 = parse(packets.at(i + 1));
		if (packet1 <= packet2)
			sum += index;
		index++;
	}
	return sum;
}

std::size_t getDecoderKey(const std::vector<std::string>& packets)
{
	const Entry dividerStart = parse("[[2]]");
	const Entry dividerEnd = parse("[[6]]");
	std::vector<Entry> vPackets = { dividerStart, dividerEnd };
	for (const auto& packet : packets)
	{
		if (packet.empty())
			continue;
		vPackets.emplace_back(parse(packet));
	}
	std::sort(
		vPackets.begin(),
		vPackets.end(),
		[](const Entry& lhs, const Entry& rhs)
		{
			return lhs < rhs;
		}
	);
	std::vector<Entry>::iterator start = std::find(vPackets.begin(), vPackets.end(), dividerStart);
	std::vector<Entry>::iterator end = std::find(vPackets.begin(), vPackets.end(), dividerEnd);
	std::size_t decoderKey = (std::distance(vPackets.begin(), start) + 1) * (std::distance(vPackets.begin(), end) + 1);
	return decoderKey;
}

void Day13()
{
	std::vector<std::string> packets = getPackets("res/Input13.txt");
	std::size_t indexSum = sumIndices(packets);
	std::size_t decoderKey = getDecoderKey(packets);
	
	std::cout << "Advent of Code 2022, Day 13" << std::endl;
	std::cout << "The sum of the indices of the pairs in the indices order: " << indexSum << std::endl;
	std::cout << "The decoder key for the distress signal: " << decoderKey << std::endl;
	std::cout << std::endl;
}