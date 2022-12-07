#include "AoC.h"

struct File
{
	std::string Path;
	std::size_t Size = 0;

	File(const std::string path, std::size_t size)
		: Path(path), Size(size)
	{

	}
};

struct Directory
{
	std::string Path;
	std::ptrdiff_t Size = -1;
	std::unordered_set<std::string> childDirectories;
	std::unordered_set<std::string> childFiles;

	Directory(const std::string& path)
		: Path(path)
	{

	}
};

std::vector<std::string> splitCommands(const std::string& command, const std::string& delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::size_t posStart = 0;
	std::size_t posEnd = 0;
	while ((posEnd = command.find(delimiter, posStart)) != std::string::npos)
	{
		token = command.substr(posStart, posEnd - posStart);
		posStart = posEnd + delimiter.length();
		tokens.push_back(token);
	}
	tokens.push_back(command.substr(posStart));
	return tokens;
}

void readInput(const std::vector<std::string>& terminal,
	std::unordered_map<std::string, Directory>& directories,
	std::unordered_map<std::string, File>& files)
{
	std::vector<std::string> workingDirectory;
	workingDirectory.push_back("/");
	directories.insert(std::make_pair("/", Directory("/")));
	for (auto& line : terminal)
	{
		std::vector<std::string> tokens = splitCommands(line, " ");
		if (tokens.at(0) == "$")
		{
			if (tokens.at(1) == "ls")
				continue;
			else
			{
				const std::string& target = tokens.at(2);
				if (target == "/")
				{
					workingDirectory.clear();
					workingDirectory.push_back("/");
				}
				else if (target == "..")
					workingDirectory.pop_back();
				else
					workingDirectory.push_back(workingDirectory.back() + target + "/");
			}
		}
		else
		{
			Directory& parent = directories.at(workingDirectory.back());
			if (tokens.at(0) == "dir")
			{
				std::string path = workingDirectory.back() + tokens.at(1) + "/";
				if (directories.find(path) == directories.end())
					directories.insert(std::make_pair(path, Directory(path)));
				parent.childDirectories.insert(path);
			}
			else
			{
				std::string path = workingDirectory.back() + tokens.at(1);
				if (files.find(path) == files.end())
					files.insert(std::make_pair(path, File(path, std::stoi(tokens.at(0)))));
				parent.childFiles.insert(path);
			}
		}
	}
}

std::vector<std::string> getTerminalOutput(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::vector<std::string> terminal;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			terminal.push_back(line);
		file.close();
	}
	return terminal;
}

std::size_t calculateDirectorySize(Directory& directory,
	const std::unordered_map<std::string, Directory>& directories,
	const std::unordered_map<std::string, File>& files)
{
	if (directory.Size >= 0)
	{
		return directory.Size;
	}
	std::size_t totalFileSize = std::accumulate(
		directory.childFiles.begin(),
		directory.childFiles.end(),
		0,
		[&](std::size_t sum, const std::string& path)
		{
			return sum + files.at(path).Size;
		}
	);
	directory.Size = std::accumulate(
		directory.childDirectories.begin(),
		directory.childDirectories.end(),
		totalFileSize,
		[&](std::size_t sum, const std::string& path)
		{
			return sum + calculateDirectorySize(const_cast<Directory&>(directories.at(path)), directories, files);
		}
	);
	return directory.Size;
}

std::unordered_map<std::string, Directory> filterDirectories(const std::unordered_map<std::string, Directory>& directories)
{
	std::unordered_map<std::string, Directory> filteredDirectories;
	for (auto& pair : directories)
		if (pair.second.Size <= 100000)
			filteredDirectories.insert(std::make_pair(pair.first, pair.second));
	return filteredDirectories;
}

std::vector<Directory> directoriesMapToVector(const std::unordered_map<std::string, Directory>& directories)
{
	std::vector<Directory> vDirectories;
	for (auto& pair : directories)
		vDirectories.push_back(pair.second);
	std::sort(
		vDirectories.begin(), 
		vDirectories.end(), 
		[](const Directory& rhs, const Directory& lhs) 
		{ 
			return rhs.Size < lhs.Size; 
		}
	);
	return vDirectories;
}

void Day7()
{
	std::vector<std::string> terminal = getTerminalOutput("res/Input7.txt");
	std::unordered_map<std::string, Directory> directories;
	std::unordered_map<std::string, File> files;
	readInput(terminal, directories, files);
	calculateDirectorySize(directories.at("/"), directories, files);
	std::unordered_map<std::string, Directory> filteredDirectories = filterDirectories(directories);
	std::size_t totalDirectorySize = std::accumulate(
		filteredDirectories.begin(),
		filteredDirectories.end(),
		0,
		[](std::size_t sum, const std::pair<std::string, Directory>& directory)
		{
			return sum + directory.second.Size;
		}
	);
	constexpr std::size_t totalSpace = 70000000;
	constexpr std::size_t requiredSpace = 30000000;
	const std::size_t freeSpace = totalSpace - directories.at("/").Size;
	const std::size_t sizeToDelete = requiredSpace - freeSpace;
	std::vector<Directory> sortedDirectories = directoriesMapToVector(directories);
	std::size_t deletedDirectorySize = 0;
	for (const auto& directory : sortedDirectories)
		if (directory.Size >= sizeToDelete)
		{
			deletedDirectorySize = directory.Size;
			break;
		}

	std::cout << "Advent of Code 2022, Day 7" << std::endl;
	std::cout << "The sum of total sizes of directories: " << totalDirectorySize << std::endl;
	std::cout << "The total size of the deleted directory: " << deletedDirectorySize << std::endl;
	std::cout << std::endl;
}