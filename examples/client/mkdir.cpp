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

int main() {

    std::map<std::string, std::string> options =
            {
                    { "webdav_hostname", "https://webdav.yandex.ru" },
                    { "webdav_login", "{webdav_login}" },
                    { "webdav_password", "{webdav_password}" }
            };

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

    auto remote_directories = {
            "existing_directory",
            "existing_directory/new_directory",
            "not_existing_directory/new_directory",
    };

    for (auto remote_directory : remote_directories) {
        bool is_created = client->create_directory(remote_directory);
        std::cout << "Directory: " << remote_directory << " is " << is_created ? "" : "not " << "created" << std::endl;
    }

    auto remote_directory = "not_existing_directory/new_directory";
    bool recursive = true;
    bool is_created = client->create_directory("not_existing_directory/new_directory", recursive);
    std::cout << "Directory: " << remote_directory << " is " << is_created ? "" : "not " << "created" << std::endl;
}

/// Directory: existing_directory is created
/// Directory: existing_directory/new_directory is created
/// Directory: not_existing_directory/new_directory is not created
/// Directory: not_existing_directory/new_directory is created
