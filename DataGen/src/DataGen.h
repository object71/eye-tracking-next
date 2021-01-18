//
// Created by capit on 1/15/2021.
//

#ifndef ENGINEHS_DATAGEN_H
#define ENGINEHS_DATAGEN_H

#include <string>
#include <vector>
#include <fstream>
#include "Filesystem.h"

void MirrorDirectories(const std::string& src, const std::string& dest);

void EnumerateFilesAndDirectories(
		const std::string& path, std::vector<std::string>& files, std::vector<std::string>& directories
);


template<typename T>
bool Contains(const std::vector<T>& collection, const T& item)
{
	return std::find(collection.begin(), collection.end(), item) != collection.end();
}

template<typename T>
std::vector<T> Difference(const std::vector<T>& left, const std::vector<T>& right)
{
	std::vector<T> diff;
	for (const T& item : left)
	{
		if (!Contains(right, item))
		{
			diff.push_back(item);
		}
	}
	
	return diff;
}

template<typename T>
std::vector<T> Intersection(const std::vector<T>& left, const std::vector<T>& right)
{
	std::vector<T> diff;
	for (const T& item : left)
	{
		if (Contains(right, item))
		{
			diff.push_back(item);
		}
	}
	
	return diff;
}

bool FileExists(const std::string& filename)
{
	return fs::exists(filename.data());
}

std::string ReadFile(const std::string& filename)
{
	if (!FileExists(filename))
	{
		return nullptr;
	}
	
	std::ifstream file(filename.data(), std::ifstream::in);
	std::string content = "";
	std::string line;
	
	while (std::getline(file, line))
	{
		content.append(line);
		content.append("\n");
	}
	
	file.close();
	
	return content;
}

unsigned int GetFileSize(const std::string& filename)
{
	if (!FileExists(filename))
	{
		return 0;
	}
	return fs::file_size(filename.data());
}

bool EndsWith(const std::string& str, const std::string& suffix)
{
	return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

bool StartsWith(const std::string& str, const std::string& prefix)
{
	return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

long long GetFileModDate(const std::string& filename)
{
	if (!FileExists(filename))
	{
		return -1;
	}
	
	fs::file_time_type time = fs::last_write_time(filename);
	return time.time_since_epoch().count();
}

std::string GetStem(const std::string& path)
{
	fs::path file(path);
	return file.stem().string();
}

std::string GetFilename(const std::string& path)
{
	fs::path file(path);
	return file.filename().string();
}

std::string GetExtension(const std::string& path)
{
	fs::path file(path);
	if (file.has_extension())
	{
		return file.extension().string();
	}
	
	return "";
}

bool IsDirectory(const std::string& path)
{
	return fs::is_directory(path);
}
#endif //ENGINEHS_DATAGEN_H
