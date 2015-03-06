#include "stdafx.h"
#include "fsinfo.hpp"
#include <sys/stat.h>

namespace FileInfo
{
	bool exists(std::wstring & path)
	{
		if (FILE *file = _wfopen(path.c_str(), L"r"))
		{
			std::fclose(file);
			return true;
		}
		return false;
	}

	bool exists(std::string & path)
	{
		if (FILE *file = fopen(path.c_str(), "r"))
		{
			std::fclose(file);
			return true;
		}
		return false;
	}

	std::wstring name(std::wstring & path)
	{
		std::wstring filename;
		std::wstring separate = L"\\";
		auto separate_position = path.find_last_of(separate);
		if (separate_position == std::wstring::npos) return path;

		auto filename_position = separate_position + 1;
		auto filename_length = path.length() - filename_position;
		filename = path.substr(filename_position, filename_length);

		return filename;
	}

	std::string name(std::string & path)
	{
		std::string filename;
		std::string separate = "\\";
		auto separate_position = path.find_last_of(separate);
		if (separate_position == std::string::npos) return path;

		auto filename_position = separate_position + 1;
		auto filename_length = path.length() - filename_position;
		filename = path.substr(filename_position, filename_length);

		return filename;
	}

	unsigned long long size(std::wstring & path_file)
	{
		struct _stat64 filestatus;
		_wstat64(path_file.c_str(), &filestatus);
		return filestatus.st_size;
	}

	unsigned long long size(std::string & path_file)
	{
		struct _stat64 filestatus;
		_stat64(path_file.c_str(), &filestatus);
		return filestatus.st_size;
	}
}