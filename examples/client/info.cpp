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

std::ostream info_to_string(std::map<std::string, std::string> & info)
{
    std::ostream stream;
    for (auto option :info)
    {
        stream << "/t" << option.first << ": " << option.second << std::endl;
    }
    return stream;
}

int main() {

    std::map<std::string, std::string> options =
            {
                    { "webdav_hostname", "https://webdav.yandex.ru" },
                    { "webdav_login", "{webdav_login}" },
                    { "webdav_password", "{webdav_password}" }
            };

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

    auto remote_resources = {
            "existing_file.dat",
            "not_existing_file.dat",
            "existing_directory",
            "not_existing_directory"
    };

    for (auto remote_resource : remote_resources)
    {
        auto info = client->info(remote_resource);
        std::cout << "Information about " << remote_resource << ":" << std::endl;
        std::cout << info_to_string(info);
        std::cout << std::endl;
    }
}

///Information about existing_file:
/// created:
/// name: existing_file
/// modified:
/// size:
/// type:
///
///Information about not_existing_file.dat:
///
///Information about existing_directory:
/// created:
/// name:
/// modified:
/// size: 0
/// type: d:collection
///
///Information about not_existing_directory:
///
