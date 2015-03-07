#pragma once

namespace FileInfo
{
	bool exists(std::string & path);

	std::string name(std::string & path);

	unsigned long long size(std::string & path_file);
}