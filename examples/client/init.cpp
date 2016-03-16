#include <webdav/client.hpp>

std::map<std::string, std::string> base_options =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "{webdav_login}" },
                { "webdav_password", "{webdav_password}" }
        };

std::map<std::string, std::string> options_with_proxy =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "{webdav_login}" },
                { "webdav_password", "{webdav_password}" },
                { "proxy_hostname", "https://10.0.0.1:8080" },
                { "proxy_login", "{proxy_login}" },
                { "proxy_password", "{proxy_password}" }
        };

std::map<std::string, std::string> options_with_cert =
        {
                { "webdav_hostname", "https://webdav.yandex.ru" },
                { "webdav_login", "{webdav_login}" },
                { "webdav_password", "{webdav_password}" },
                { "cert_path", "/etc/ssl/certs/client.crt" },
                { "key_path", "/etc/ssl/private/client.key" }
        };

std::ostream options_to_string(std::map<std::string, std::string> & options)
{
    std::ostream stream;
    for (auto option :options)
    {
        stream << "\t" << option.first << ": " << option.second << std::endl;
    }
    return stream;
}

int main() {

    auto various_options = {
            base_options,
            options_with_proxy,
            options_with_cert
    };

    for (auto options : various_options) {
		std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
        bool is_connected = client->check();
        std::cout << "Client with options: " << std::endl;
        std::cout << options_to_string(options);
        std::cout << " is " << is_connected ? " " : "not " << "connected" << std::endl;
        std::cout << endl;
    }
}

/// Client with options:
///
