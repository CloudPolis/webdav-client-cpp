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

    auto hostname_ptr = std::getenv("WEBDAV_HOSTNAME");
    auto username_ptr = std::getenv("WEBDAV_USERNAME");
    auto password_ptr = std::getenv("WEBDAV_PASSWORD");
    auto root_ptr = std::getenv("WEBDAV_ROOT");

    if (hostname_ptr == nullptr) return -1;
    if (username_ptr == nullptr) return -1;
    if (password_ptr == nullptr) return -1;

    std::map<std::string, std::string> options =
    {
        { "webdav_hostname", hostname_ptr },
        { "webdav_username", username_ptr },
        { "webdav_password", password_ptr }
    };

    if (root_ptr != nullptr) {
        options["webdav_root"] = root_ptr;
    }

    std::unique_ptr<WebDAV::Client> client{ new WebDAV::Client{ options } };

    auto remote_resources = {
        "existing_file.dat",
        "not_existing_file.dat",
        "existing_directory",
        "existing_directory/",
        "not_existing_directory",
        "not_existing_directory/"
    };

    for (const auto& remote_resource : remote_resources) {
        bool is_existed = client->check(remote_resource);
        std::cout << "Resource: " << remote_resource << " is " << (is_existed ? "" : "not ") << "existed" << std::endl;
    }
}

/// Resource: existing_file.dat is existed
/// Resource: not_existing_file.dat is not existed
/// Resource: existing_file.dat is existed
/// Resource: existing_directory is existed
/// Resource: existing_directory/ is existed
/// Resource: not_existing_directory is not existed
/// Resource: not_existing_directory/ is not existed
