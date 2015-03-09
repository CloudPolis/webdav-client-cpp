#pragma once

namespace WebDAV
{
	class Client
	{
		enum { buffer_size = 1000 * 1000 };

		void init() noexcept;

		std::string webdav_hostname;
		std::string webdav_login;
		std::string webdav_password;

		std::string proxy_hostname;
		std::string proxy_login;
		std::string proxy_password;

		std::string cert_path;
		std::string key_path;

		std::map<std::string, std::string> options() noexcept;

		bool sync_download(std::string remote_file, std::string local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr) noexcept;
		bool sync_download_to(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr) noexcept;

		bool sync_upload(std::string remote_file, std::string local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr) noexcept;
		bool sync_upload_from(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr) noexcept;


	public:

		// Options:
		// - Required:
		//    - webdav_hostname
		//    - webdav_login
		//    - webdav_password
		// - Optional:
		//    - proxy_hostname
		//    - proxy_login
		//    - proxy_password
		//    - cert_path
		//    - key_path
		Client(std::map<std::string, std::string> options) noexcept;

		~Client() noexcept;

		long long free_size() noexcept;

		bool check(std::string remote_resource = "/", std::string remote_root = "") noexcept;

		std::map<std::string, std::string> info(std::string remote_resource, std::string remote_root = "") noexcept;

		bool clean(std::string remote_resource, std::string remote_root = "") noexcept;

		bool is_dir(std::string remote_resource, std::string remote_root) noexcept;

		std::vector<std::string> list(std::string remote_directory = "", std::string remote_root = "") noexcept;

		bool create_directory(std::string remote_directory, bool recursive = false) noexcept;

		bool move(std::string remote_source_resource, std::string remote_destination_resource) noexcept;

		bool copy(std::string remote_source_resource, std::string remote_destination_resource) noexcept;

		bool download(std::string remote_file, std::string local_file, std::string remote_root = "") noexcept;

		bool download_to(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "") noexcept;

		void async_download(std::string remote_file, std::string local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr) noexcept;

		void async_download_to(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr) noexcept;

		bool upload(std::string remote_file, std::string local_file, std::string remote_root = "") noexcept;

		bool upload_from(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "") noexcept;

		void async_upload(std::string remote_file, std::string local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr) noexcept;

		void async_upload_from(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr) noexcept;
	};
}