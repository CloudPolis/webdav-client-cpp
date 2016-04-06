#include "stdafx.h"
#include "fsinfo.hpp"

namespace WebDAV
{
	namespace FileInfo
	{
		bool exists(std::string & path)
		{
			std::ifstream file(path);
			return file.good();
		}
	
		std::string name(std::string & path) {
			std::string filename;
			std::string separate = "\\";
			auto separate_position = path.find_last_of(separate);
			if (separate_position == std::string::npos) return path;
	
			auto filename_position = separate_position + 1;
			auto filename_length = path.length() - filename_position;
			filename = path.substr(filename_position, filename_length);
	
			return filename;
		}
	
		unsigned long long size(std::string & path_file)
		{
			std::ifstream file(path_file, std::ios::binary | std::ios::ate);
			return (unsigned long long)file.tellg();
		}
	}
}
