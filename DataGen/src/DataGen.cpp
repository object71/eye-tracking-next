//
// Created by capit on 1/15/2021.
//

#include "DataGen.h"
#include "spdlog/spdlog.h"

int main(int argc, char** argv)
{
	spdlog::set_level(spdlog::level::debug);
	spdlog::info("Data generation started");
	
	if (argc != 3)
	{
		spdlog::critical("Cannot generate data! Invalid number of arguments.");
		
		for (int i = 0; i < argc; i++)
		{
			spdlog::debug(argv[i]);
		}
		
		return 1;
	}
	
	MirrorDirectories(fmt::format("{}/data", argv[1]), fmt::format("{}/data", argv[2]));
	
	spdlog::info("Data generation ended");
	return 0;
}

void MirrorDirectories(const std::string& src, const std::string& dest)
{
	if (!fs::exists(dest))
	{
		fs::create_directory(dest);
	}
	
	std::vector<std::string> srcFiles;
	std::vector<std::string> srcDirectories;
	EnumerateFilesAndDirectories(src, srcFiles, srcDirectories);
	
	std::vector<std::string> destFiles;
	std::vector<std::string> destDirectories;
	EnumerateFilesAndDirectories(dest, destFiles, destDirectories);
	
	std::vector<std::string> extraDirectories = Difference(destDirectories, srcDirectories);
	std::vector<std::string> extraFiles = Difference(destFiles, srcFiles);
	
	for (const std::string& path : extraDirectories)
	{
		spdlog::debug(fmt::format("Deleting extra directory (recursively): {}", path));
		fs::remove_all(fmt::format("{}/{}", dest, path));
	}
	
	for (const std::string& path : extraFiles)
	{
		spdlog::debug(fmt::format("Deleting extra file: {}", path));
		fs::remove(fmt::format("{}/{}", dest, path));
	}
	
	std::vector<std::string> newDirectories = Difference(srcDirectories, destDirectories);
	std::vector<std::string> newFiles = Difference(srcFiles, destFiles);
	
	for (const std::string& path : newDirectories)
	{
		spdlog::debug(fmt::format("Creating new directory: {}", path));
		fs::copy(fmt::format("{}/{}", src, path), fmt::format("{}/{}", dest, path), fs::copy_options::recursive);
	}
	
	for (const std::string& path : newFiles)
	{
		spdlog::debug(fmt::format("Creating new file: {}", path));
		fs::copy_file(fmt::format("{}/{}", src, path), fmt::format("{}/{}", dest, path));
	}
	
	std::vector<std::string> matchingDirectories = Intersection(srcDirectories, destDirectories);
	std::vector<std::string> matchingFiles = Intersection(srcFiles, destFiles);
	
	for (const std::string& path : matchingDirectories)
	{
		spdlog::debug(fmt::format("Enumerating recursively: {}", path));
		MirrorDirectories(fmt::format("{}/{}", src, path), fmt::format("{}/{}", dest, path));
	}
	
	for (const std::string& path : matchingFiles)
	{

		if (GetFileModDate(fmt::format("{}/{}", src, path)) > GetFileModDate(fmt::format("{}/{}", dest, path)))
		{
			spdlog::debug(fmt::format("Updating file: {}", path));
			fs::copy_file(fmt::format("{}/{}", src, path), fmt::format("{}/{}", dest, path), fs::copy_options::overwrite_existing);
		}
	}
}

void EnumerateFilesAndDirectories(
		const std::string& path, std::vector<std::string>& files, std::vector<std::string>& directories
)
{
	for (auto& content : fs::directory_iterator(path))
	{
		if (IsDirectory(content.path().string()))
		{
			directories.push_back(content.path().filename().string());
		}
		else
		{
			files.push_back(content.path().filename().string());
		}
	}
}
