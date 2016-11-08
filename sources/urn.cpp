/*#***************************************************************************
#                         __    __   _____       _____
#   Project              |  |  |  | |     \     /  ___|
#                        |  |__|  | |  |\  \   /  /
#                        |        | |  | )  ) (  (     
#                        |   /\   | |  |/  /   \  \___
#                         \_/  \_/  |_____/     \_____|
#
# Copyright (C) 2016, The WDC Project, <designerror@yandex.ru>, et al.
#
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution. 
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the LICENSE file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
############################################################################*/

#include <algorithm>
#include <vector>
#include <curl/curl.h>

#include "urn.hpp"

namespace WebDAV {

	const std::string Urn::separate = "/";

	Urn::Urn(std::string path, bool directory) {
		if (path.empty()) path = Urn::separate;
		auto first_position = path.find(Urn::separate);
		if (first_position != 0) path = Urn::separate + path;
		auto last_symbol_index = path.length() - 1;
		auto last_symbol = std::string{path[last_symbol_index]};
		auto is_dir = Urn::separate.compare(last_symbol) == 0;
		if (directory && !is_dir) path += Urn::separate;
		m_path = path;

		auto double_separte = Urn::separate + Urn::separate;
		bool isFind = false;
		do {
			auto first_position = m_path.find(double_separte);
			isFind = first_position != std::string::npos;
			if (isFind) m_path.replace(first_position, double_separte.size(), Urn::separate);
		} while (isFind);
	}

	Urn::Urn(std::nullptr_t) {
		m_path = nullptr;
	}

	std::string Urn::path() {
		return m_path;
	}

	std::string escape(void *request, std::string& name) {
		
		std::string path = curl_easy_escape(request, name.c_str(), (int)name.length());
		return path;
	}

	std::vector<std::string> split(const std::string& text, const std::string& delims)
	{
		std::vector<std::string> tokens;
		std::size_t start = text.find_first_not_of(delims), end = 0;

		while ((end = text.find_first_of(delims, start)) != std::string::npos)
		{
			tokens.push_back(text.substr(start, end - start));
			start = text.find_first_not_of(delims, end);
		}
		if (start != std::string::npos)
			tokens.push_back(text.substr(start));

		return tokens;
	}

	std::string Urn::quote(void *request) {
		if (this->is_root()) return m_path;
		auto names = split(m_path, Urn::separate);
		std::string quote_path;
		std::for_each(names.begin(), names.end(), [&quote_path, request](std::string& name) {
			auto escape_name = escape(request, name);
			quote_path.append(Urn::separate);
			quote_path.append(escape_name);
		});
		if (is_directory()) quote_path.append(Urn::separate);
		return quote_path;
	}

	std::string Urn::name() {
		auto path = this->path();
		auto is_root = Urn::separate.compare(path) == 0;
		if (is_root) return std::string{""};

		if (this->is_directory())
		{
			auto path_without_slash = path.substr(0, path.length() - 1);
			auto pre_last_separate_position = path_without_slash.rfind(Urn::separate);
			auto name = path.substr(pre_last_separate_position + 1);
			return name;
		}
		else
		{
			auto last_separate_position = path.rfind(Urn::separate);
			auto name = path.substr(last_separate_position + 1);
			return name;
		}
	}

	std::string Urn::parent() {
		if (this->is_root()) return m_path;

		auto last_separate_position = m_path.rfind(Urn::separate);
		if (last_separate_position == 0) return Urn::separate;

		auto parent = m_path.substr(0, last_separate_position + 1);
		return parent;
	}

	bool Urn::is_directory() {
		auto path = this->path();
		auto last_symbol_index = path.length() - 1;
		auto last_symbol = std::string{path[last_symbol_index]};
		auto is_equal = Urn::separate.compare(last_symbol) == 0;
		return is_equal;
	}

	bool Urn::is_root() {
		return Urn::separate.compare(m_path) == 0;
	}

	Urn Urn::operator+(std::string resource_path) {
		bool is_directory = this->is_directory();
		if (!is_directory) return *this;
		auto directory_path = this->path();
		resource_path = directory_path + resource_path;
		return Urn(resource_path);
	}
}
