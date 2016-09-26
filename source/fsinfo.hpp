#pragma once

namespace WebDAV
{
	namespace FileInfo
	{
		auto exists(const std::string& path) -> bool;
	
		auto size(const std::string& path_file) -> unsigned long long;
	}
}
