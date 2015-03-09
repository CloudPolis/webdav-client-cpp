#include "stdafx.h"
#include "urn.hpp"
#include <curl/curl.h>

namespace WebDAV {

	const std::string Urn::separate = "/";

	Urn::Urn(std::string path, bool directory) {
		if (path.empty()) path = Urn::separate;
		auto first_position = path.find_first_of(Urn::separate);
		if (first_position != 0) path = Urn::separate + path;
		auto last_symbol_index = path.length() - 1;
		auto last_symbol = std::string{path[last_symbol_index]};
		auto is_dir = Urn::separate.compare(last_symbol) == 0;
		if (directory && !is_dir) path += Urn::separate;
		m_path = path;
	}

	Urn::Urn(std::nullptr_t) {
		m_path = nullptr;
	}

	std::string Urn::path() {
		return m_path;
	}

	std::string Urn::quote(void *request) {
		int length = 0;
		std::string path = curl_easy_unescape(request, m_path.c_str(), (int) m_path.length(), &length);
		return path;
	}

	std::string Urn::name() {
		auto path = this->path();
		auto is_root = Urn::separate.compare(path) == 0;
		if (is_root) return std::string{""};

		auto last_separate_position = path.find_last_of(Urn::separate);

		auto name = path.substr(last_separate_position + 1);
		return name;
	}

	std::string Urn::parent() {
		auto path = this->path();
		auto is_root = Urn::separate.compare(path) == 0;
		if (is_root) return path;

		auto last_separate_position = path.find_last_of(Urn::separate);
		if (last_separate_position == 0) return Urn::separate;

		auto parent = path.substr(0, last_separate_position + 1);
		return parent;
	}

	bool Urn::is_dir() {
		auto path = this->path();
		auto last_symbol_index = path.length() - 1;
		auto last_symbol = std::string{path[last_symbol_index]};
		auto is_equal = Urn::separate.compare(last_symbol) == 0;
		return is_equal;
	}

	Urn Urn::operator+(std::string resource_path) {
		bool is_directory = this->is_dir();
		if (!is_directory) return nullptr;
		auto directory_path = this->path();
		resource_path = directory_path + resource_path;
		return Urn(resource_path);
	}
}