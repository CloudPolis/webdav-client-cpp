#pragma once

#include "client.hpp"

#include <curl/curl.h>

namespace WebDAV
{
	class Request
	{
		std::map<std::string, std::string> options;

		bool proxy_enabled();

		bool cert_required();

	public:

		Request(std::map<std::string, std::string> options);

		~Request();

		template<typename T>
		bool set(CURLoption option, T value);

		//bool set(CURLoption option, char * value);

		//bool set(CURLoption option, const char * value);

		//bool set(CURLoption option, int value);

		//bool set(CURLoption option, long long value);

		bool perform();

		void * handle;
	};
}