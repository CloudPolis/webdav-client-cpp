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

#include "request.hpp"
#include "fsinfo.hpp"

namespace WebDAV
{
	auto inline get(const dict_t& options, const std::string&& name) -> std::string
	{
		auto it = options.find(name);
		if (it == options.end()) return "";
		else return it->second;
	}

	Request::Request(dict_t&& options_) : options(options_)
	{
		auto webdav_hostname = get(options, "webdav_hostname");
		auto webdav_login = get(options, "webdav_login");
		auto webdav_password = get(options, "webdav_password");

		auto proxy_hostname = get(options, "proxy_hostname");
		auto proxy_login = get(options, "proxy_login");
		auto proxy_password = get(options, "proxy_password");

		auto cert_path = get(options, "cert_path");
		auto key_path = get(options, "key_path");

		this->handle = curl_easy_init();

		this->set(CURLOPT_SSL_VERIFYHOST, 0);
		this->set(CURLOPT_SSL_VERIFYPEER, 0);

#ifdef _DEBUG
		this->set(CURLOPT_VERBOSE, 1);
#else
		this->set(CURLOPT_VERBOSE, 0);
#endif
		if (this->cert_required()){

			this->set(CURLOPT_SSLCERTTYPE, "PEM");
			this->set(CURLOPT_SSLKEYTYPE, "PEM");
			this->set(CURLOPT_SSLCERT, (char *)cert_path.c_str());
			this->set(CURLOPT_SSLKEY, (char *)key_path.c_str());

		}
		
		this->set(CURLOPT_URL, (char *)webdav_hostname.c_str());
		this->set(CURLOPT_HTTPAUTH, (int)CURLAUTH_BASIC);
		auto token = webdav_login + ":" + webdav_password;
		this->set(CURLOPT_USERPWD, (char *)token.c_str());

		if (!this->proxy_enabled()) return;

		this->set(CURLOPT_PROXY, (char *)proxy_hostname.c_str());
		this->set(CURLOPT_PROXYAUTH, (int)CURLAUTH_BASIC);

		if (proxy_login.empty()) return;

		if (proxy_password.empty())
		{
			this->set(CURLOPT_PROXYUSERNAME, (char *)proxy_login.c_str());
		}
		else
		{
			token = proxy_login + ":" + proxy_password;
			this->set(CURLOPT_PROXYUSERPWD, (char *)token.c_str());
		}
	}

	Request::~Request() noexcept
	{
		if (this->handle != nullptr) curl_easy_cleanup(this->handle);
	}


	bool Request::perform() const noexcept
	{
		if (this->handle == nullptr) return false;
		auto is_performed = check_code(curl_easy_perform(this->handle));
		if (!is_performed) return false;
		long http_code = 0;
		curl_easy_getinfo(this->handle, CURLINFO_RESPONSE_CODE, &http_code);
		if (http_code < 200 || http_code > 299) return false;
		return true;
	}

	bool Request::proxy_enabled() const noexcept
	{
		auto proxy_hostname = get(options, "proxy_hostname");
		auto proxy_login = get(options, "proxy_login");
		auto proxy_password = get(options, "proxy_password");
		bool proxy_hostname_presented = !proxy_hostname.empty();
		if (!proxy_hostname_presented) return false;
		bool proxy_login_presented = !proxy_login.empty();
		bool proxy_password_presented = !proxy_password.empty();
		if (proxy_password_presented && !proxy_login_presented) return false;
		return true;
	}

	bool Request::cert_required() const noexcept
	{
		const auto cert_path = get(options, "cert_path");
		const auto key_path = get(options, "key_path");
		if (cert_path.empty()) return false;
		bool cert_is_existed = FileInfo::exists(cert_path);
		if (!cert_is_existed) return false;
		if (key_path.empty()) return false;
		return FileInfo::exists(key_path);
	}
}
