#pragma once

<<<<<<< HEAD
=======
#include "client.hpp"

>>>>>>> 90cc2f2fe27b0ad5d2cc3b1b79a9a2f33f30d57f
#include <curl/curl.h>

namespace WebDAV
{
	class Request
	{
		std::map<std::string, std::string> options;

		bool proxy_enabled() noexcept;

		bool cert_required() noexcept;

	public:

		Request(std::map<std::string, std::string> options) noexcept;

		~Request() noexcept;

		bool set(CURLoption option, size_t value) noexcept;

		bool set(CURLoption option, long value) noexcept;

		bool set(CURLoption option, struct curl_slist * value) noexcept;

		bool set(CURLoption option, int value) noexcept;

		bool set(CURLoption option, const char * value) noexcept;

		bool set(CURLoption option, curl_off_t value) noexcept;

		bool perform() noexcept;

		void * handle;
	};
}