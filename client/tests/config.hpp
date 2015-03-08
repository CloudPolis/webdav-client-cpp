//#define WITH_PROXY

static std::map<std::string, std::string> options_with_proxy = 
{ 
	{ "webdav_hostname", "https://webdav.yandex.ru" },
	{ "webdav_login", "designerror" },
	{ "webdav_password", "{webdav_password}" },
	{ "proxy_hostname", "https://10.0.0.1:8080" },
	{ "proxy_login", "designerror" },
	{ "proxy_password", "{proxy_password}" }
};

static std::map<std::string, std::string> options_without_proxy =
{
	{ "webdav_hostname", "https://webdav.yandex.ru" },
	{ "webdav_login", "designerror" },
	{ "webdav_password", "{webdav_password}" }
};

#ifdef WITH_PROXY
static std::map<std::string, std::string> options = options_with_proxy;
#else
static std::map<std::string, std::string> options = options_without_proxy;
#endif

static std::string file_content = "static std::wstring file_content = L\"static std::wstring file_content = ...\";";