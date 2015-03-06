#pragma once

#pragma region INCLUDE_WINAPI
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma endregion

#pragma region INCLUDE_STL
#include <memory>
#if _MSC_VER >= 1800
#include <chrono>
#include <thread>
#endif
#pragma endregion

#pragma region INCLUDE_STRING
#include <tchar.h>
#include <string>
#ifdef UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif
#define t(text) _T(text)
#pragma endregion

#pragma region INCLUDE_WEBDAV
#include <functional>
#include <map>
#include <vector>

#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#include <WebDAV/Client.hpp>

#ifdef _DEBUG
	#if _MSC_VER == 1600
		#pragma comment(lib, "webdav_client-v100-sgd.lib")
		#pragma comment(lib, "libcurl-vc100-sgd.lib")
	#else if _MSC_VER == 1800
		#pragma comment(lib, "webdav_client-v120_xp-sgd.lib")
		#pragma comment(lib, "libcurl-v120_xp-sgd.lib")
	#endif
#else
	#if _MSC_VER == 1600
		#pragma comment(lib, "webdav_client-v100-s.lib")
		#pragma comment(lib, "libcurl-vc100-s.lib")
	#else if _MSC_VER == 1800
		#pragma comment(lib, "webdav_client-v120_xp-s.lib")
		#pragma comment(lib, "libcurl-v120_xp-s.lib")
	#endif
#endif
#pragma endregion

#include "Config.hpp"