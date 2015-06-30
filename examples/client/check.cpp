#include <webdav/client.hpp>

int main() {

    std::map<std::string, std::string> options =
            {
                    { "webdav_hostname", "https://webdav.yandex.ru" },
                    { "webdav_login", "{webdav_login}" },
                    { "webdav_password", "{webdav_password}" }
            };


    WebDAV::Client client(options);

    auto remote_resources = {
            "existing_file.dat",
            "not_existing_file.dat",
            "existing_directory",
            "existing_directory/",
            "not_existing_directory",
            "not_existing_directory/"
    };

    for (auto remote_resource : remote_resources) {
        bool is_existed = client.check(remote_resource);
        std::cout << "Resource: " << remote_resource << " is " << is_existed ? "" : "not " << "existed" << std::endl;
    }
}

/// Resource: existing_file.dat is existed
/// Resource: not_existing_file.dat is not existed
/// Resource: existing_file.dat is existed
/// Resource: existing_directory is existed
/// Resource: existing_directory/ is existed
/// Resource: not_existing_directory is not existed
/// Resource: not_existing_directory/ is not existed
