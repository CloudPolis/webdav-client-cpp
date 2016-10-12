//#define WITH_PROXY

#include <map>

static std::map<std::string, std::string> options_with_proxy = 
{ 
	{ "webdav_hostname", 	"https://webdav.yandex.ru" },
	{ "webdav_login", 		"webdav.test.login" },
	{ "webdav_password", 	"webdav.test.password" },
	{ "proxy_hostname", 	"{proxy_hostname}" },
	{ "proxy_login", 		"{proxy_login}" },
	{ "proxy_password", 	"{proxy_password}" }
};

static std::map<std::string, std::string> options_without_proxy =
{
	{ "webdav_hostname", 	"webdav.yandex.ru:443" },
	{ "webdav_root", 		"/" },
	{ "webdav_login", 		"webdav.test.login" },
	{ "webdav_password", 	"webdav.test.password" }
};

#ifdef WITH_PROXY
static std::map<std::string, std::string> options = options_with_proxy;
#else
static std::map<std::string, std::string> options = options_without_proxy;
#endif

static std::string file_content = "static std::wstring file_content = L\"static std::wstring file_content = ...\";";