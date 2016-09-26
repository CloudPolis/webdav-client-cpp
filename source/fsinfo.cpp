#include "stdafx.h"
#include "fsinfo.hpp"

namespace WebDAV
{
	namespace FileInfo
	{
		auto exists(const std::string& path) -> bool
		{
			std::ifstream file(path);
			return file.good();
		}
	
		auto size(const std::string& path_file) -> unsigned long long 
		{
			std::ifstream file(path_file, std::ios::binary | std::ios::ate);
			return (unsigned long long)file.tellg();
		}
	}
}
