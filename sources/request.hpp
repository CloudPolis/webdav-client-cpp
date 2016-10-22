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

#ifndef WEBDAV_REQUEST_H
#define WEBDAV_REQUEST_H
#pragma once

#include <curl/curl.h>
#include <string>
#include <map>

namespace WebDAV
{
	bool inline check_code(CURLcode code)
	{
		return code == CURLE_OK;
	}

	using dict_t = std::map<std::string, std::string>; 
	
	class Request
	{
		const dict_t options;

		bool proxy_enabled() const noexcept;

		bool cert_required() const noexcept;

	public:

		Request(dict_t&& options);

		~Request() noexcept;

		template <typename T>
		auto set(CURLoption option, T value) const noexcept -> bool
		{
			if (this->handle == nullptr) return false;
			return check_code(curl_easy_setopt(this->handle, option, value));
		}
		
		bool perform() const noexcept;

		void * handle;
	};
}

#endif
