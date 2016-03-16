#include "stdafx.h"
#include "urn.hpp"
#include <curl/curl.h>

namespace WebDAV {

	const std::string Urn::separate = "/";

	Urn::Urn(std::string path, bool directory) {
		if (path.empty()) path = Urn::separate;
<<<<<<< HEAD
		auto first_position = path.find(Urn::separate);
=======
		auto first_position = path.find_first_of(Urn::separate);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
		if (first_position != 0) path = Urn::separate + path;
		auto last_symbol_index = path.length() - 1;
		auto last_symbol = std::string{path[last_symbol_index]};
		auto is_dir = Urn::separate.compare(last_symbol) == 0;
		if (directory && !is_dir) path += Urn::separate;
		m_path = path;
<<<<<<< HEAD

		auto double_separte = Urn::separate + Urn::separate;
		bool isFind = false;
		do {
			auto first_position = m_path.find(double_separte);
			isFind = first_position != std::string::npos;
			if (isFind) m_path.replace(first_position, double_separte.size(), Urn::separate);
		} while (isFind);
=======
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
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

		if (this->is_dir())
		{
			auto path_without_slash = path.substr(0, path.length() - 1);
<<<<<<< HEAD
			auto pre_last_separate_position = path_without_slash.rfind(Urn::separate);
=======
			auto pre_last_separate_position = path_without_slash.find_last_of(Urn::separate);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
			auto name = path.substr(pre_last_separate_position + 1);
			return name;
		}
		else
		{
<<<<<<< HEAD
			auto last_separate_position = path.rfind(Urn::separate);
=======
			auto last_separate_position = path.find_last_of(Urn::separate);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
			auto name = path.substr(last_separate_position + 1);
			return name;
		}
	}

	std::string Urn::parent() {
		auto path = this->path();
		auto is_root = Urn::separate.compare(path) == 0;
		if (is_root) return path;

<<<<<<< HEAD
		auto last_separate_position = path.rfind(Urn::separate);
=======
		auto last_separate_position = path.find_last_of(Urn::separate);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
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
<<<<<<< HEAD
		if (!is_directory) return *this;
=======
		if (!is_directory) return nullptr;
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
		auto directory_path = this->path();
		resource_path = directory_path + resource_path;
		return Urn(resource_path);
	}
<<<<<<< HEAD
}
=======
}
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
