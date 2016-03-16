#include <webdav/client.hpp>

std::ostream info_to_string(std::map<std::string, std::string> & info)
{
    std::ostream stream;
    for (auto option :info)
    {
        stream << "/t" << option.first << ": " << option.second << std::endl;
    }
    return stream;
}

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

    auto remote_resources = {
            "existing_file.dat",
            "not_existing_file.dat",
            "existing_directory",
            "not_existing_directory"
    };

    for (auto remote_resource : remote_resources)
    {
<<<<<<< HEAD
        auto info = client->info(remote_resource);
=======
        auto info = client.info(remote_resource);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
        std::cout << "Information about " << remote_resource << ":" << std::endl;
        std::cout << info_to_string(info);
        std::cout << std::endl;
    }
}

///Information about existing_file:
/// created:
/// name: existing_file
/// modified:
/// size:
/// type:
///
///Information about not_existing_file.dat:
///
<<<<<<< HEAD
///Information about existing_directory:
=======
///Information about existing_file:
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
/// created:
/// name:
/// modified:
/// size: 0
/// type: d:collection
///
///Information about not_existing_directory:
///
