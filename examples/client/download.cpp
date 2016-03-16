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


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

<<<<<<< HEAD
    bool is_downloaded = client->download(remote_file, local_file);
=======
    bool is_downloaded = client.download(remote_file, local_file);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

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


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

<<<<<<< HEAD
    client->async_download(remote_file, local_file, [&remote_file](bool is_downloaded)
=======
    client.async_download(remote_file, local_file, [&remote_file](bool is_downloaded)
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
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


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_file = "dir/file.dat";
    char * buffer_ptr = nullptr;
    long long int buffer_size = 0;

<<<<<<< HEAD
    bool is_downloaded = client->download(remote_file, buffer_ptr, buffer_size);
=======
    bool is_downloaded = client.download(remote_file, buffer_ptr, buffer_size);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

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


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_file = "dir/file.dat";
    char * buffer_ptr = nullptr;
    long long int buffer_size = 0;

<<<<<<< HEAD
    client->async_download(remote_file, buffer_ptr, buffer_size, [&remote_file](bool is_downloaded)
=======
    client.async_download(remote_file, buffer_ptr, buffer_size, [&remote_file](bool is_downloaded)
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
    {
        std::cout << remote_file << " resource is" << is_downloaded ? "" : "not" << "downloaded" << std::endl;
    });
}

/// dir/file.dat resource is downloaded

//! [async_download_to_buffer]
