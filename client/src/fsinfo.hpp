#pragma once

namespace FileInfo
{
	bool exists(std::wstring & path);

	bool exists(std::string & path);

	std::wstring name(std::wstring & path);

	std::string name(std::string & path);

	unsigned long long size(std::wstring & path_file);

	unsigned long long size(std::string & path_file);
}