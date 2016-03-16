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


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

<<<<<<< HEAD
    bool is_uploaded = client->upload(remote_file, local_file);
=======
    bool is_uploaded = client.upload(remote_file, local_file);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

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


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_file = "dir/file.dat";
    auto local_file = "/home/user/Downloads/file.dat";

<<<<<<< HEAD
    client->async_upload(remote_file, local_file, [&remote_file](bool is_uploaded)
=======
    client.async_upload(remote_file, local_file, [&remote_file](bool is_uploaded)
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
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


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_file = "dir/file.dat";
    char * buffer_ptr = nullptr;
    long long int buffer_size = 0;

<<<<<<< HEAD
    bool is_uploaded = client->upload(remote_file, buffer_ptr, buffer_size);
=======
    bool is_uploaded = client.upload(remote_file, buffer_ptr, buffer_size);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

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


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_file = "dir/file.dat";
    char * buffer_ptr = nullptr;
    long long int buffer_size = 0;

<<<<<<< HEAD
    client->async_upload(remote_file, buffer_ptr, buffer_size, [&remote_file](bool is_uploaded)
=======
    client.async_upload(remote_file, buffer_ptr, buffer_size, [&remote_file](bool is_uploaded)
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
    {
        std::cout << remote_file << " resource is" << is_uploaded ? "" : "not" << "uploaded" << std::endl;
    });
}

/// dir/file.dat resource is uploaded

//! [async_upload_from_buffer]
