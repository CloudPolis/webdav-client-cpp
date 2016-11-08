/*#***************************************************************************
#                         __    __   _____       _____
#   Project              |  |  |  | |     \     /  ___|
#                        |  |__|  | |  |\  \   /  /
#                        |        | |  | )  ) (  (
#                        |   /\   | |  |/  /   \  \___
#                         \_/  \_/  |_____/     \_____|
#
# Copyright (C) 2016, The WDC Project, <designerror@yandex.ru>, et al.
#
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution.
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the LICENSE file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
############################################################################*/

#include <thread>
#include <webdav/client.hpp>
#include "pugiext.hpp"
#include "header.hpp"
#include "request.hpp"
#include "urn.hpp"
#include "fsinfo.hpp"
#include "callback.hpp"

namespace WebDAV
{
	using progress_funptr = int(*)(void *context, size_t dltotal, size_t dlnow, size_t ultotal, size_t ulnow);

	auto inline get(const dict_t& options, const std::string&& name) -> std::string
	{
		auto it = options.find(name);
		if (it == options.end()) return "";
		else return it->second;
	}

	class ClientImpl : public Client
	{
	public:

		void init() const noexcept;

		std::string webdav_hostname;
		std::string webdav_root;
		std::string webdav_login;
		std::string webdav_password;

		std::string proxy_hostname;
		std::string proxy_login;
		std::string proxy_password;

		std::string cert_path;
		std::string key_path;

		dict_t options() const noexcept;

		bool sync_download(
			const std::string& remote_file,
			const std::string& local_file,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept;

		bool sync_download_to(
			const std::string& remote_file,
			char * & buffer_ptr,
			unsigned long long int & buffer_size,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept;

		bool sync_download_to(
			const std::string& remote_file,
			std::ostream& stream,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept;

		bool sync_upload(
			const std::string& remote_file,
			const std::string& local_file,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept;

		bool sync_upload_from(
			const std::string& remote_file,
			char * buffer_ptr,
			unsigned long long int buffer_size,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept;

		bool sync_upload_from(
			const std::string& remote_file,
			std::istream& stream,
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) const noexcept;

		ClientImpl(const dict_t & options);

		~ClientImpl();
	};

	inline ClientImpl * GetImpl(Client * ptr) { return (ClientImpl *)ptr; }
	inline const ClientImpl * GetImpl(const Client * ptr) { return (const ClientImpl *)ptr; }

	ClientImpl::ClientImpl(const dict_t& options)
	{
		this->webdav_hostname = get(options, "webdav_hostname");
		this->webdav_root = get(options, "webdav_root");
		this->webdav_login = get(options, "webdav_login");
		this->webdav_password = get(options, "webdav_password");

		this->proxy_hostname = get(options, "proxy_hostname");
		this->proxy_login = get(options, "proxy_login");
		this->proxy_password = get(options, "proxy_password");

		this->cert_path = get(options, "cert_path");
		this->key_path = get(options, "key_path");

		this->init();
	}

	void
		ClientImpl::init() const noexcept
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);
	}

	dict_t
		ClientImpl::options() const noexcept
	{
		return dict_t
		{
			{ "webdav_hostname", this->webdav_hostname },
			{ "webdav_root", this->webdav_root },
			{ "webdav_login", this->webdav_login },
			{ "webdav_password", this->webdav_password },
			{ "proxy_hostname", this->proxy_hostname },
			{ "proxy_login", this->proxy_login },
			{ "proxy_password", this->proxy_password },
			{ "cert_path", this->cert_path },
			{ "key_path", this->key_path },
		};
	}

	bool
		ClientImpl::sync_download(
			const std::string& remote_file,
			const std::string& local_file,
			callback_t callback,
			progress_t progress
		) const noexcept

	{
		bool is_existed = this->check(remote_file);
		if (!is_existed) return false;

		auto root_urn = Urn(this->webdav_root, true);
		auto file_urn = root_urn + remote_file;

		std::ofstream file_stream(local_file, std::ios::binary);

		Request request(this->options());

		auto url = this->webdav_hostname + file_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "GET");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HEADER, 0L);
		request.set(CURLOPT_WRITEDATA, (size_t)&file_stream);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Write::stream);
		if (progress != nullptr) {
			request.set(CURLOPT_XFERINFOFUNCTION, (size_t)progress.target<progress_funptr>());
			request.set(CURLOPT_NOPROGRESS, 0L);
		}

		bool is_performed = request.perform();

		if (callback != nullptr) callback(is_performed);
		return is_performed;
	}

	bool
		ClientImpl::sync_download_to(
			const std::string& remote_file,
			char * & buffer_ptr,
			unsigned long long int & buffer_size,
			callback_t callback,
			progress_t progress
		) const noexcept
	{
		bool is_existed = this->check(remote_file);
		if (!is_existed) return false;

		auto root_urn = Urn(this->webdav_root, true);
		auto file_urn = root_urn + remote_file;

		Data data = { 0, 0, 0 };

		Request request(this->options());

		auto url = this->webdav_hostname + file_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "GET");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HEADER, 0L);
		request.set(CURLOPT_WRITEDATA, (size_t)&data);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Append::buffer);
		if (progress != nullptr) {
			request.set(CURLOPT_XFERINFOFUNCTION, (size_t)progress.target<progress_funptr>());
			request.set(CURLOPT_NOPROGRESS, 0L);
		}

		bool is_performed = request.perform();
		if (callback != nullptr) callback(is_performed);
		if (!is_performed) return false;

		buffer_ptr = data.buffer;
		buffer_size = data.size;
		return true;
	}

	bool
		ClientImpl::sync_download_to(
			const std::string& remote_file,
			std::ostream & stream,
			callback_t callback,
			progress_t progress
		) const noexcept
	{
		bool is_existed = this->check(remote_file);
		if (!is_existed) return false;

		auto root_urn = Urn(this->webdav_root, true);
		auto file_urn = root_urn + remote_file;

		Request request(this->options());

		auto url = this->webdav_hostname + file_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "GET");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HEADER, 0L);
		request.set(CURLOPT_WRITEDATA, (size_t)&stream);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Write::stream);
		if (progress != nullptr) {
			request.set(CURLOPT_XFERINFOFUNCTION, (size_t)progress.target<progress_funptr>());
			request.set(CURLOPT_NOPROGRESS, 0L);
		}

		bool is_performed = request.perform();
		if (callback != nullptr) callback(is_performed);
		if (!is_performed) return false;

		return true;
	}

	bool
		ClientImpl::sync_upload(
			const std::string& remote_file,
			const std::string& local_file,
			callback_t callback,
			progress_t progress
		) const noexcept
	{
		bool is_existed = FileInfo::exists(local_file);
		if (!is_existed) return false;

		auto root_urn = Urn(this->webdav_root, true);
		auto file_urn = root_urn + remote_file;

		std::ifstream file_stream(local_file, std::ios::binary);
		auto size = FileInfo::size(local_file);

		Request request(this->options());

		auto url = this->webdav_hostname + file_urn.quote(request.handle);

		Data response = { 0, 0, 0 };

		request.set(CURLOPT_UPLOAD, 1L);
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_READDATA, (size_t)&file_stream);
		request.set(CURLOPT_READFUNCTION, (size_t)Callback::Read::stream);
		request.set(CURLOPT_INFILESIZE_LARGE, (curl_off_t)size);
		request.set(CURLOPT_BUFFERSIZE, (long)Client::buffer_size);
		request.set(CURLOPT_WRITEDATA, (size_t)&response);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Append::buffer);
		if (progress != nullptr) {
			request.set(CURLOPT_XFERINFOFUNCTION, (size_t)progress.target<progress_funptr>());
			request.set(CURLOPT_NOPROGRESS, 0L);
		}

		bool is_performed = request.perform();

		if (callback != nullptr) callback(is_performed);
		return is_performed;
	}

	bool
		ClientImpl::sync_upload_from(
			const std::string& remote_file,
			char * buffer,
			unsigned long long int buffer_size,
			callback_t callback,
			progress_t progress
		) const noexcept
	{
		auto root_urn = Urn(this->webdav_root, true);
		auto file_urn = root_urn + remote_file;

		Data data = { buffer, 0, buffer_size };

		Request request(this->options());

		auto url = this->webdav_hostname + file_urn.quote(request.handle);

		Data response = { 0, 0, 0 };

		request.set(CURLOPT_UPLOAD, 1L);
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_READDATA, (size_t)&data);
		request.set(CURLOPT_READFUNCTION, (size_t)Callback::Read::buffer);
		request.set(CURLOPT_INFILESIZE_LARGE, (curl_off_t)buffer_size);
		request.set(CURLOPT_BUFFERSIZE, (long)Client::buffer_size);
		request.set(CURLOPT_WRITEDATA, (size_t)&response);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Append::buffer);
		if (progress != nullptr) {
			request.set(CURLOPT_XFERINFOFUNCTION, (size_t)progress.target<progress_funptr>());
			request.set(CURLOPT_NOPROGRESS, 0L);
		}

		bool is_performed = request.perform();

		if (callback != nullptr) callback(is_performed);
		return is_performed;
	}

	bool
		ClientImpl::sync_upload_from(
			const std::string& remote_file,
			std::istream& stream,
			callback_t callback,
			progress_t progress
		) const noexcept
	{
		auto root_urn = Urn(this->webdav_root, true);
		auto file_urn = root_urn + remote_file;

		Request request(this->options());

		auto url = this->webdav_hostname + file_urn.quote(request.handle);
		stream.seekg(0, std::ios::end);
		size_t stream_size = stream.tellg();
		stream.seekg(0, std::ios::beg);

		Data response = { 0, 0, 0 };

		request.set(CURLOPT_UPLOAD, 1L);
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_READDATA, (size_t)&stream);
		request.set(CURLOPT_READFUNCTION, (size_t)Callback::Read::stream);
		request.set(CURLOPT_INFILESIZE_LARGE, (curl_off_t)stream_size);
		request.set(CURLOPT_BUFFERSIZE, (long)Client::buffer_size);
		request.set(CURLOPT_WRITEDATA, (size_t)&response);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Append::buffer);
		if (progress != nullptr) {
			request.set(CURLOPT_XFERINFOFUNCTION, (size_t)progress.target<progress_funptr>());
			request.set(CURLOPT_NOPROGRESS, 0L);
		}

		bool is_performed = request.perform();

		if (callback != nullptr) callback(is_performed);
		return is_performed;
	}

	Client* Client::Init(const dict_t& options) noexcept
	{
		return new ClientImpl(options);
	}

	ClientImpl::~ClientImpl() {
	}

	void Client::Cleanup() noexcept
	{
		curl_global_cleanup();
	}

	unsigned long long
		Client::free_size() const noexcept
	{
		Header header = {
			"Accept: */*",
			"Depth: 0",
			"Content-Type: text/xml"
		};

		pugi::xml_document document;
		auto propfind = document.append_child("D:propfind");
		propfind.append_attribute("xmlns:D") = "DAV:";

		auto prop = propfind.append_child("D:prop");
		prop.append_child("D:quokta-available-bytes");
		prop.append_child("D:quota-used-bytes");

		auto document_print = pugi::node_to_string(document);
		size_t size = document_print.length() * sizeof((document_print.c_str())[0]);

		Data data = { 0, 0, 0 };

		Request request(GetImpl(this)->options());

		request.set(CURLOPT_CUSTOMREQUEST, "PROPFIND");
		request.set(CURLOPT_HTTPHEADER, (struct curl_slist *)header.handle);
		request.set(CURLOPT_POSTFIELDS, document_print.c_str());
		request.set(CURLOPT_POSTFIELDSIZE, (long)size);
		request.set(CURLOPT_HEADER, 0);
		request.set(CURLOPT_WRITEDATA, (size_t)&data);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Append::buffer);

		auto is_performed = request.perform();
		if (!is_performed) return 0;

		document.load_buffer(data.buffer, (size_t)data.size);

		pugi::xml_node multistatus = document.select_single_node("d:multistatus").node();
		pugi::xml_node response = multistatus.select_single_node("d:response").node();
		pugi::xml_node propstat = response.select_single_node("d:propstat").node();
		prop = propstat.select_single_node("d:prop").node();
		pugi::xml_node quota_available_bytes = prop.select_single_node("d:quota-available-bytes").node();
		std::string free_size_text = quota_available_bytes.first_child().value();

		auto free_size = atol(free_size_text.c_str());
		return free_size;
	}

	bool
		Client::check(const std::string& remote_resource) const noexcept
	{
		auto clientImpl = GetImpl(this);
		auto root_urn = Urn(clientImpl->webdav_root, true);
		auto resource_urn = root_urn + remote_resource;

		Header header = {
			"Accept: */*",
			"Depth: 1"
		};

		Data data = { 0, 0, 0 };

		Request request(clientImpl->options());

		auto url = clientImpl->webdav_hostname + resource_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "PROPFIND");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HTTPHEADER, (struct curl_slist *)header.handle);
		request.set(CURLOPT_WRITEDATA, (size_t)&data);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Append::buffer);

		return request.perform();
	}

	dict_t
		Client::info(const std::string& remote_resource) const noexcept
	{
		auto clientImpl = GetImpl(this);
		auto root_urn = Urn(clientImpl->webdav_root, true);
		auto target_urn = root_urn + remote_resource;

		Header header = {
			"Accept: */*",
			"Depth: 1"
		};

		Data data = { 0, 0, 0 };

		Request request(clientImpl->options());

		auto url = clientImpl->webdav_hostname + target_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "PROPFIND");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HTTPHEADER, (struct curl_slist *)header.handle);
		request.set(CURLOPT_WRITEDATA, (size_t)&data);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Append::buffer);

		bool is_performed = request.perform();

		if (!is_performed) return dict_t();

		pugi::xml_document document;
		document.load_buffer(data.buffer, (size_t)data.size);
		auto multistatus = document.select_single_node("d:multistatus").node();
		auto responses = multistatus.select_nodes("d:response");
		for (auto response : responses)
		{
			pugi::xml_node href = response.node().select_single_node("d:href").node();
			std::string encode_file_name = href.first_child().value();
			std::string resource_path = curl_unescape(encode_file_name.c_str(), (int)encode_file_name.length());
			auto target_path = target_urn.path();
			auto target_path_without_sep = std::string(target_path, 0, target_path.rfind("/") + 1);
			auto resource_path_without_sep = std::string(resource_path, 0, resource_path.rfind("/") + 1);
			if (resource_path_without_sep.compare(target_path_without_sep) == 0) {
				auto propstat = response.node().select_single_node("d:propstat").node();
				auto prop = propstat.select_single_node("d:prop").node();
				auto creation_date = prop.select_single_node("d:creationdate").node();
				auto display_name = prop.select_single_node("d:displayname").node();
				auto content_length = prop.select_single_node("d:getcontentlength").node();
				auto modified_date = prop.select_single_node("d:getlastmodified").node();
				auto resource_type = prop.select_single_node("d:resourcetype").node();

				dict_t information = {
					{ "created", creation_date.first_child().value() },
					{ "name", display_name.first_child().value() },
					{ "size", content_length.first_child().value() },
					{ "modified", modified_date.first_child().value() },
					{ "type", resource_type.first_child().name() }
				};

				return information;
			}
		}

		return dict_t();
	}

	bool
		Client::is_dir(const std::string& remote_resource) const noexcept
	{
		auto information = this->info(remote_resource);
		auto resource_type = information["type"];
		bool is_directory = resource_type.compare("d:collection") == 0;
		return is_directory;
	}

	strings_t
		Client::list(const std::string& remote_directory) const noexcept
	{
		auto clientImpl = GetImpl(this);
		bool is_existed = this->check(remote_directory);
		if (!is_existed) return strings_t();

		bool is_directory = this->is_dir(remote_directory);
		if (!is_directory) return strings_t();
		auto target_urn = Urn(clientImpl->webdav_root, true) + remote_directory;
		target_urn = Urn(target_urn.path(), true);

		Header header = {
			"Accept: */*",
			"Depth: 1"
		};

		Data data = { 0, 0, 0 };

		Request request(clientImpl->options());

		auto url = clientImpl->webdav_hostname + target_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "PROPFIND");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HTTPHEADER, (struct curl_slist *)header.handle);
		request.set(CURLOPT_HEADER, 0);
		request.set(CURLOPT_WRITEDATA, (size_t)&data);
		request.set(CURLOPT_WRITEFUNCTION, (size_t)Callback::Append::buffer);

		bool is_performed = request.perform();

		if (!is_performed) return strings_t();

		strings_t resources;

		pugi::xml_document document;
		document.load_buffer(data.buffer, (size_t)data.size);
		auto multistatus = document.select_single_node("d:multistatus").node();
		auto responses = multistatus.select_nodes("d:response");
		for (auto response : responses)
		{
			pugi::xml_node href = response.node().select_single_node("d:href").node();
			std::string encode_file_name = href.first_child().value();
			std::string resource_path = curl_unescape(encode_file_name.c_str(), (int)encode_file_name.length());
			auto target_path = target_urn.path();
			if (resource_path == target_path) continue;
			Urn resource_urn(resource_path);
			resources.push_back(resource_urn.name());
		}

		return resources;
	}

	bool Client::download(
		const std::string& remote_file,
		const std::string& local_file,
		progress_t progress
	) const noexcept
	{
		auto clientImpl = GetImpl(this);
		return clientImpl->sync_download(remote_file, local_file, nullptr, progress);
	}

	void
		Client::async_download(
			const std::string& remote_file,
			const std::string& local_file,
			callback_t callback,
			progress_t progress
		) const noexcept
	{
		auto clientImpl = GetImpl(this);
		std::thread downloading([&]() { clientImpl->sync_download(remote_file, local_file, callback, progress); });
		downloading.detach();
	}

	bool
		Client::download_to(
			const std::string& remote_file,
			char * & buffer_ptr,
			unsigned long long int & buffer_size,
			progress_t progress
		) const noexcept
	{
		auto clientImpl = GetImpl(this);
		return clientImpl->sync_download_to(remote_file, buffer_ptr, buffer_size, nullptr, progress);
	}

	bool
		Client::download_to(
			const std::string& remote_file,
			std::ostream& stream,
			progress_t progress
		) const noexcept
	{
		auto clientImpl = GetImpl(this);
		return clientImpl->sync_download_to(remote_file, stream, nullptr, progress);
	}

	bool
		Client::create_directory(const std::string& remote_directory, bool recursive) const noexcept
	{
		auto clientImpl = GetImpl(this);
		bool is_existed = this->check(remote_directory);
		if (is_existed) return true;

		bool resource_is_dir = true;
		Urn directory_urn(remote_directory, resource_is_dir);

		if (recursive) {
			auto remote_parent_directory = directory_urn.parent();
			bool is_created = this->create_directory(remote_parent_directory, true);
			if (!is_created) return false;
		}

		Header header = {
			"Accept: */*",
			"Connection: Keep-Alive"
		};

		auto target_urn = Urn(clientImpl->webdav_root, true) + remote_directory;
		target_urn = Urn(target_urn.path(), true);

		Request request(clientImpl->options());

		auto url = clientImpl->webdav_hostname + target_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "MKCOL");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HTTPHEADER, (struct curl_slist *)header.handle);

		return request.perform();
	}

	bool
		Client::move(const std::string& remote_source_resource, const std::string& remote_destination_resource) const noexcept
	{
		auto clientImpl = GetImpl(this);
		bool is_existed = this->check(remote_source_resource);
		if (!is_existed) return false;

		Urn root_urn(clientImpl->webdav_root, true);

		auto source_resource_urn = root_urn + remote_source_resource;
		auto destination_resource_urn = root_urn + remote_destination_resource;

		Header header = {
			"Accept: */*",
			"Destination: " + destination_resource_urn.path()
		};

		Request request(clientImpl->options());

		auto url = clientImpl->webdav_hostname + source_resource_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "MOVE");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HTTPHEADER, (struct curl_slist *)header.handle);

		return request.perform();
	}

	bool
		Client::copy(const std::string& remote_source_resource, const std::string& remote_destination_resource) const noexcept
	{
		auto clientImpl = GetImpl(this);
		bool is_existed = this->check(remote_source_resource);
		if (!is_existed) return false;

		Urn root_urn(clientImpl->webdav_root, true);

		auto source_resource_urn = root_urn + remote_source_resource;
		auto destination_resource_urn = root_urn + remote_destination_resource;

		Header header = {
			"Accept: */*",
			"Destination: " + destination_resource_urn.path()
		};

		Request request(clientImpl->options());

		auto url = clientImpl->webdav_hostname + source_resource_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "COPY");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HTTPHEADER, (struct curl_slist *)header.handle);

		return request.perform();
	}

	bool
		Client::upload(
			const std::string& remote_file,
			const std::string& local_file,
			progress_t progress
		) const noexcept
	{
		auto clientImpl = GetImpl(this);
		return clientImpl->sync_upload(remote_file, local_file, nullptr, progress);
	}

	void
		Client::async_upload(
			const std::string& remote_file,
			const std::string& local_file,
			callback_t callback,
			progress_t progress
		) const noexcept
	{
		auto clientImpl = GetImpl(this);
		std::thread uploading([&]() { clientImpl->sync_upload(remote_file, local_file, callback, progress); });
		uploading.detach();
	}

	bool
		Client::upload_from(
			const std::string& remote_file,
			std::istream& stream,
			progress_t progress
		) const noexcept
	{
		auto clientImpl = GetImpl(this);
		return clientImpl->sync_upload_from(remote_file, stream, nullptr, progress);
	}

	bool
		Client::upload_from(
			const std::string& remote_file,
			char * buffer_ptr,
			unsigned long long int buffer_size,
			progress_t progress
		) const noexcept
	{
		auto clientImpl = GetImpl(this);
		return clientImpl->sync_upload_from(remote_file, buffer_ptr, buffer_size, nullptr, progress);
	}

	bool
		Client::clean(const std::string& remote_resource) const noexcept
	{
		auto clientImpl = GetImpl(this);
		bool is_existed = this->check(remote_resource);
		if (!is_existed) return true;

		auto root_urn = Urn(clientImpl->webdav_root, true);
		auto resource_urn = root_urn + remote_resource;

		Header header = {
			"Accept: */*",
			"Connection: Keep-Alive"
		};

		Request request(clientImpl->options());

		auto url = clientImpl->webdav_hostname + resource_urn.quote(request.handle);

		request.set(CURLOPT_CUSTOMREQUEST, "DELETE");
		request.set(CURLOPT_URL, url.c_str());
		request.set(CURLOPT_HTTPHEADER, (struct curl_slist *)header.handle);

		return request.perform();
	}
}
