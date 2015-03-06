//#define WITH_PROXY

static std::map<std::string, std::string> options_with_proxy = 
{ 
	{ "webdav_hostname", "https://webdav.yandex.ru" },
	{ "webdav_login", "designerror" },
	{ "webdav_password", "yxKeksiki_8" },
	{ "proxy_hostname", "https://10.0.0.188:8080" },
	{ "proxy_login", "gvc05svc" },
	{ "proxy_password", "Wad9jnr3" }
};

static std::map<std::string, std::string> options_without_proxy =
{
	{ "webdav_hostname", "https://webdav.yandex.ru" },
	{ "webdav_login", "designerror" },
	{ "webdav_password", "yxKeksiki_8" }
};

#ifdef WITH_PROXY
static std::map<std::string, std::string> options = options_with_proxy;
#else
static std::map<std::string, std::string> options = options_without_proxy;
#endif

static std::string file_content = "static std::wstring file_content = L\"static std::wstring file_content = ...\";";