#pragma once

namespace WebDAV
{
	namespace FileInfo
	{
		bool exists(const std::string& path);
	
		std::string name(const std::string& path);
	
		unsigned long long size(const std::string& path_file);
	}
}
