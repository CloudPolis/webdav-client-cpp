#include <webdav/client.hpp>

//! [download_to_file]

void download_to_file()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };


    WebDAV::Client client(options);

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

    bool is_downloaded = client.download(remote_file, local_file);

    std::cout << remote_file << " resource is" << is_downloaded ? "" : "not" << "downloaded" << std::endl;
}

/// dir/file.dat resource is downloaded

//! [download_to_file]

//! [async_download_to_file]

void async_download_to_file()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };


    WebDAV::Client client(options);

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

    client.async_download(remote_file, local_file, [&remote_file](bool is_downloaded)
    {
        std::cout << remote_file << " resource is" << is_downloaded ? "" : "not" << "downloaded" << std::endl;
    });
}

/// dir/file.dat resource is downloaded

//! [async_download_to_file]

//! [download_to_buffer]

void download_to_buffer()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };


    WebDAV::Client client(options);

    auto remote_file = "dir/file.dat";
    char * buffer_ptr = nullptr;
    long long int buffer_size = 0;

    bool is_downloaded = client.download(remote_file, buffer_ptr, buffer_size);

    std::cout << remote_file << " resource is" << is_downloaded ? "" : "not" << "downloaded" << std::endl;
}

/// dir/file.dat resource is downloaded

//! [download_to_buffer]

//! [async_download_to_buffer]

void async_download_to_buffer()
{
    std::map<std::string, std::string> options =
            {
                    {"webdav_hostname", "https://webdav.yandex.ru"},
                    {"webdav_login", "{webdav_login}"},
                    {"webdav_password", "{webdav_password}"}
            };


    WebDAV::Client client(options);

    auto remote_file = "dir/file.dat";
    char * buffer_ptr = nullptr;
    long long int buffer_size = 0;

    client.async_download(remote_file, buffer_ptr, buffer_size, [&remote_file](bool is_downloaded)
    {
        std::cout << remote_file << " resource is" << is_downloaded ? "" : "not" << "downloaded" << std::endl;
    });
}

/// dir/file.dat resource is downloaded

//! [async_download_to_buffer]
