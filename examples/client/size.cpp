#include <webdav/client.hpp>

int main() {

    std::map<std::string, std::string> options =
            {
                    { "webdav_hostname", "https://webdav.yandex.ru" },
                    { "webdav_login", "{webdav_login}" },
                    { "webdav_password", "{webdav_password}" }
            };


    WebDAV::Client client(options);

    auto free_size = client.free_size();
    std::cout << "Free size: " << free_size << " bytes" << std::endl;
}

/// Free size: 8234213123 bytes
