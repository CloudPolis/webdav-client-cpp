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

#include <memory>
#include <sstream>

std::string resources_to_string(const std::vector<std::string> & resources) {
    std::stringstream stream;
    for (const auto& resource : resources)
    {
        stream << "\t" << "- " << resource << std::endl;
    }
    return stream.str();
}

int main() {

    std::map<std::string, std::string> options =
    {
        { "webdav_hostname", "https://webdav.yandex.ru" },
        { "webdav_username", "{webdav_username}" },
        { "webdav_password", "{webdav_password}" }
    };

    std::unique_ptr<WebDAV::Client> client{ new WebDAV::Client{ options } };

    auto remote_file = "file.dat";
    auto remote_directory = "dir/";
    auto new_remote_file = "file2.dat";
    auto new_remote_directory = "dir2/";

    auto resources = client->list();
    std::cout << "\"/\" resource contain:" << std::endl;
    std::cout << resources_to_string(resources) << std::endl;

    client->move(remote_file, new_remote_file);
    client->move(remote_directory, new_remote_directory);

    resources = client->list();
    std::cout << "\"/\" resource contain:" << std::endl;
    std::cout << resources_to_string(resources) << std::endl;
}

/// "/" resource contain:
/// - dir/
/// - file.dat
///
/// "/" resource contain:
/// - dir2/
/// - file2.dat
