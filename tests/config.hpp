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

//#define WITH_PROXY

#include <map>

static std::map<std::string, std::string> options_with_proxy = 
{ 
	{ "webdav_hostname", 	"https://webdav.yandex.ru" },
	{ "webdav_login", 		"webdav.test.login" },
	{ "webdav_password", 	"webdav.test.password" },
	{ "proxy_hostname", 	"{proxy_hostname}" },
	{ "proxy_login", 		"{proxy_login}" },
	{ "proxy_password", 	"{proxy_password}" }
};

static std::map<std::string, std::string> options_without_proxy =
{
	{ "webdav_hostname", 	"https://webdav.yandex.ru" },
	{ "webdav_login", 	"webdav.test.login" },
	{ "webdav_password", 	"webdav.test.password" }
};

#ifdef WITH_PROXY
static std::map<std::string, std::string> options = options_with_proxy;
#else
static std::map<std::string, std::string> options = options_without_proxy;
#endif

static std::string file_content = "static std::wstring file_content = L\"static std::wstring file_content = ...\";";
