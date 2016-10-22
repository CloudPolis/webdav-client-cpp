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

#include <webdav/client.hpp>

std::map<std::string, std::string> base_options =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "{webdav_login}" },
                { "webdav_password", "{webdav_password}" }
        };

std::map<std::string, std::string> options_with_proxy =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "{webdav_login}" },
                { "webdav_password", "{webdav_password}" },
                { "proxy_hostname", "https://10.0.0.1:8080" },
                { "proxy_login", "{proxy_login}" },
                { "proxy_password", "{proxy_password}" }
        };

std::map<std::string, std::string> options_with_cert =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "{webdav_login}" },
                { "webdav_password", "{webdav_password}" },
                { "cert_path", "/etc/ssl/certs/client.crt" },
                { "key_path", "/etc/ssl/private/client.key" }
        };

std::ostream options_to_string(std::map<std::string, std::string> & options)
{
    std::ostream stream;
    for (auto option :options)
    {
        stream << "\t" << option.first << ": " << option.second << std::endl;
    }
    return stream;
}

int main() {

    auto various_options = {
            base_options,
            options_with_proxy,
            options_with_cert
    };

    for (auto options : various_options) {
		std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
        bool is_connected = client->check();
        std::cout << "Client with options: " << std::endl;
        std::cout << options_to_string(options);
        std::cout << " is " << is_connected ? " " : "not " << "connected" << std::endl;
        std::cout << endl;
    }
}

/// Client with options:
///
