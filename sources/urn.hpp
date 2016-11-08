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

#ifndef WEBDAV_URN_H
#define WEBDAV_URN_H
#pragma once

#include <string>

namespace WebDAV
{
	class Urn {
		static const std::string separate;

		std::string m_path;

	public:

		Urn(std::string path, bool directory = false);

		Urn(std::nullptr_t);

		std::string path();

		std::string quote(void *request);

		std::string name();

		std::string parent();

		bool is_directory();

		bool is_root();

		Urn operator+(std::string resource_path);
	};
}

#endif
