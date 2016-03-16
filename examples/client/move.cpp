#include <webdav/client.hpp>

std::ostream resources_to_string(std::vector<std::string> & resources)
{
    std::ostream stream;
    for (auto resource : resources)
    {
        stream << "\t" << "- " << resource << std::endl;
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

    auto remote_file = "file.dat";
    auto remote_directory = "dir/";
    auto new_remote_file = "file2.dat";
    auto new_remote_directory = "dir2/";

<<<<<<< HEAD
    auto resources = client->list();
    std::cout << "\"/\" resource contain:" << std::endl;
    std::cout << resources_to_string(resources) << std::endl;

    client->move(remote_file, new_remote_file);
    client->move(remote_directory, new_remote_directory);
=======
    auto resources = client.list();
    std::cout << "\"/\" resource contain:" << std::endl;
    std::cout << resources_to_string(resources) << std::endl;

    client.move(remote_file, new_remote_file);
    client.move(remote_directory, new_remote_directory);
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f

    resources = client.list();
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
