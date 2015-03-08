#include <client.hpp>
#include <iostream>

std::map<std::string, std::string> base_options =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "designerror" },
                { "webdav_password", "{webdav_password}" }
        };

std::map<std::string, std::string> options_with_proxy =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "designerror" },
                { "webdav_password", "{webdav_password}" },
                { "proxy_hostname", "https://10.0.0.1:8080" },
                { "proxy_login", "designerror" },
                { "proxy_password", "{proxy_password}" }
        };

std::map<std::string, std::string> options_with_cert =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "designerror" },
                { "webdav_password", "{webdav_password}" },
                { "cert_path", "/etc/ssl/certs/client.crt" },
                { "key_path", "/etc/ssl/private/client.key" }
        };

int main() {

    auto various_options = {
            base_options,
            options_with_proxy,
            options_with_cert
    };

    for (auto options : various_options) {
        WebDAV::Client client(options);
        bool is_connected = client.check();
        std::cout << "Client with options: " << std::endl;
        std::cout << options << std::endl;
        std::cout << " is " << is_connected ? " " : "not " << "connected" << std::endl;
    }
}