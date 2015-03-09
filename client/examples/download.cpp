#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <client.hpp>

int main() {

    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };


    WebDAV::Client client(options);

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

    client.download(remote_file, local_file);

    client.async_download(remote_file, local_file, [&remote_file](bool is_downloaded)
    {
        std::cout << remote_file << " resource is" << is_downloaded ? "" : "not" << "downloaded" << std::endl;
    });
}

/// dir/file.dat resource is downloaded