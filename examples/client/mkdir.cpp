#include <webdav/client.hpp>

int main() {

    std::map<std::string, std::string> options =
            {
                    { "webdav_hostname", "https://webdav.yandex.ru" },
                    { "webdav_login", "{webdav_login}" },
                    { "webdav_password", "{webdav_password}" }
            };


<<<<<<< HEAD
	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
=======
    WebDAV::Client client(options);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    auto remote_directories = {
            "existing_directory",
            "existing_directory/new_directory",
            "not_existing_directory/new_directory",
    };

    for (auto remote_directory : remote_directories) {
<<<<<<< HEAD
        bool is_created = client->create_directory(remote_directory);
=======
        bool is_created = client.create_directory(remote_directory);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
        std::cout << "Directory: " << remote_directory << " is " << is_existed ? "" : "not " << "created" << std::endl;
    }

    auto remote_directory = "not_existing_directory/new_directory";
    bool recursive = true;
<<<<<<< HEAD
    bool is_created = client->create_directory("not_existing_directory/new_directory", recursive);
=======
    bool is_created = client.create_directory("not_existing_directory/new_directory", recursive);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
    std::cout << "Directory: " << remote_directory << " is " << is_existed ? "" : "not " << "created" << std::endl;
}

/// Directory: existing_directory is created
/// Directory: existing_directory/new_directory is created
/// Directory: not_existing_directory/new_directory is not created
/// Directory: not_existing_directory/new_directory is created
