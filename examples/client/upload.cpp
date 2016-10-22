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

//! [upload_from_file]

void upload_from_file()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };


	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

    bool is_uploaded = client->upload(remote_file, local_file);

    std::cout << remote_file << " resource is" << is_uploaded ? "" : "not" << "uploaded" << std::endl;
}

/// dir/file.dat resource is uploaded

//! [upload_from_file]

//! [async_upload_from_file]

void async_upload_from_file()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

    client->async_upload(remote_file, local_file, [remote_file](bool is_uploaded)
    {
        std::cout << remote_file << " resource is" << is_uploaded ? "" : "not" << "uploaded" << std::endl;
    });
}

/// dir/file.dat resource is uploaded

//! [async_upload_from_file]

//! [upload_from_buffer]

void upload_from_buffer()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

    auto remote_file = "dir/file.dat";
    char * buffer_ptr = nullptr;
    long long int buffer_size = 0;

    bool is_uploaded = client->upload(remote_file, buffer_ptr, buffer_size);

    std::cout << remote_file << " resource is" << is_uploaded ? "" : "not" << "uploaded" << std::endl;
}

/// dir/file.dat resource is uploaded

//! [upload_from_buffer]

//! [async_upload_from_buffer]

void async_upload_from_buffer()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

    auto remote_file = "dir/file.dat";
    char * buffer_ptr = nullptr;
    long long int buffer_size = 0;

    client->async_upload(remote_file, buffer_ptr, buffer_size, [remote_file](bool is_uploaded)
    {
        std::cout << remote_file << " resource is" << is_uploaded ? "" : "not" << "uploaded" << std::endl;
    });
}

/// dir/file.dat resource is uploaded

//! [async_upload_from_buffer]

//! [upload_from_stream]

void upload_from_stream()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };

    std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

    auto remote_file = "dir/file.dat";
    std::ifstream stream("/home/user/Downloads/file.dat");

    bool is_uploaded = client->upload_from(remote_file, stream);

    std::cout << remote_file << " resource is" << is_uploaded ? "" : "not" << "uploaded" << std::endl;
}

/// dir/file.dat resource is uploaded

//! [upload_from_stream]
