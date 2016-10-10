#pragma once

#include <curl/curl.h>
#include <string>
#include <map>

namespace WebDAV
{
	bool inline check_code(CURLcode code)
	{
		return code == CURLE_OK;
	}

	using dict_t = std::map<std::string, std::string>; 
	
	class Request
	{
		const dict_t options;

		bool proxy_enabled() const noexcept;

		bool cert_required() const noexcept;

	public:

		Request(dict_t&& options);

		~Request() noexcept;

		template <typename T>
		auto set(CURLoption option, T value) const noexcept -> bool
		{
			if (this->handle == nullptr) return false;
			return check_code(curl_easy_setopt(this->handle, option, value));
		}
		
		bool perform() const noexcept;

		void * handle;
	};
}
