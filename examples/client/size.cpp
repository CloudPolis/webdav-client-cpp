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

    auto free_size = client->free_size();
=======
    WebDAV::Client client(options);

    auto free_size = client.free_size();
>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
    std::cout << "Free size: " << free_size << " bytes" << std::endl;
}

/// Free size: 8234213123 bytes
