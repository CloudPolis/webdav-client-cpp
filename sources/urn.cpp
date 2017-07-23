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
#include <string>
#include <vector>
#include <curl/curl.h>

using std::string;
using std::vector;

#include "urn.hpp"

namespace WebDAV {

    namespace Urn {

        const string Path::separate = "/";
        const string Path::root = "/";

        Path::Path(const string& path_, bool force_dir) {

            string path = path_;
            if (path_.empty()) path = Path::root;
            auto first_position = path.find(Path::separate);
            if (first_position != 0) path = Path::root + path;
            auto last_symbol_index = path.length() - 1;
            auto last_symbol = string{ path[last_symbol_index] };
            auto is_dir = Path::separate.compare(last_symbol) == 0;
            if (force_dir && !is_dir) path += Path::separate;
            m_path = path;

            auto double_separte = Path::separate + Path::separate;
            bool is_find = false;
            do {
                auto first_position = m_path.find(double_separte);
                is_find = first_position != string::npos;
                if (is_find) {
                    m_path.replace(first_position, double_separte.size(), Path::separate);
                }
            } while (is_find);
        }

        Path::Path(std::nullptr_t) {
            m_path = nullptr;
        }

        auto Path::path() const -> string {
            return m_path;
        }

        auto escape(void * request, const string& name) -> string {
            
            string path = curl_easy_escape(request, name.c_str(), (int)name.length());
            return path;
        }

        auto split(const string& text, const string& delims) -> vector<string> {

            vector<string> tokens;
            std::size_t start = text.find_first_not_of(delims), end = 0;

            while ((end = text.find_first_of(delims, start)) != string::npos)
            {
                tokens.push_back(text.substr(start, end - start));
                start = text.find_first_not_of(delims, end);
            }
            if (start != string::npos)
                tokens.push_back(text.substr(start));

            return tokens;
        }

        auto Path::quote(void *request) const -> string {

            if (this->is_root()) return m_path;

            auto names = split(m_path, Path::separate);
            std::string quote_path;

            std::for_each(names.begin(), names.end(), [&quote_path, request](string& name) {
                auto escape_name = escape(request, name);
                quote_path.append(Path::separate);
                quote_path.append(escape_name);
            });

            if (is_directory()) {
                quote_path.append(Path::separate);
            }
            return quote_path;
        }

        auto Path::name() const -> string {

            auto path = this->path();
            auto is_root = Path::separate.compare(path) == 0;
            if (is_root) return string{""};

            if (this->is_directory()) {

                auto path_without_slash = path.substr(0, path.length() - 1);
                auto pre_last_separate_position = path_without_slash.rfind(Path::separate);
                auto name = path.substr(pre_last_separate_position + 1);
                return name;
            }
            else {

                auto last_separate_position = path.rfind(Path::separate);
                auto name = path.substr(last_separate_position + 1);
                return name;
            }
        }

        auto Path::parent() const -> Path {

            if (this->is_root()) return m_path;

            auto last_separate_position = m_path.rfind(Path::separate);
            if (last_separate_position == 0) return Path::separate;

            auto parent = m_path.substr(0, last_separate_position + 1);
            return parent;
        }

        auto Path::is_directory() const -> bool {

            auto path = this->path();
            auto last_symbol_index = path.length() - 1;
            auto last_symbol = std::string{path[last_symbol_index]};
            auto is_equal = Path::separate.compare(last_symbol) == 0;
            return is_equal;
        }

        auto Path::is_root() const -> bool {
            return Path::separate.compare(m_path) == 0;
        }

        auto Path::operator+(const string& resource_path) const -> Path {

            return Path{ m_path + resource_path };
        }

        auto Path::operator==(const Path& rhs) const -> bool {
           
            if (this->is_root()) {
                if (rhs.is_root()) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else if (rhs.is_root()) {
                return false;
            }

            string lhs_path;
            bool is_dir = is_directory();
            if (is_dir) {
                lhs_path = m_path.substr(0, m_path.length()-1);
            }
            else {
                lhs_path = m_path;
            }
            string rhs_path;
            if (rhs.is_directory()) {
                rhs_path = rhs.path();
                rhs_path = rhs_path.substr(0, rhs_path.length()-1);
            }
            else {
                rhs_path = rhs.path();
            }
            return lhs_path == rhs_path;
        }
    }
}
