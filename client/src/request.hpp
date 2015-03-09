#pragma once

#include "client.hpp"

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

		template<typename T>
		bool set(CURLoption option, T value) noexcept;

		bool perform() noexcept;

		void * handle;
	};
}