#pragma once

namespace WebDAV
{
	class Client
	{
		enum { buffer_size = 1000 * 1000 };

		void init();

		std::string webdav_hostname;
		std::string webdav_login;
		std::string webdav_password;

		std::string proxy_hostname;
		std::string proxy_login;
		std::string proxy_password;

		std::string cert_path;
		std::string key_path;

		std::map<std::string, std::string> options();

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
		Client(std::map<std::string, std::string> options);

		~Client();

		long long free_size();

		bool check(std::string remote_resource = "/", std::string remote_root = "");

		std::map<std::string, std::string> info(std::string remote_resource, std::string remote_root = "");

		bool clean(std::string remote_resource, std::string remote_root = "");

		bool is_dir(std::string remote_resource, std::string remote_root);

		std::vector<std::string> list(std::string remote_directory = "", std::string remote_root = "");

		bool download(std::string remote_file, std::string local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		bool download_to(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		void async_download(std::string remote_file, std::string local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		void async_download_to(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		bool create_directory(std::string remote_directory);

		bool upload(std::string remote_file, std::string local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		bool upload_from(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		void async_upload(std::string remote_file, std::string local_file, std::string remote_root = "", std::function<void(bool)> callback = nullptr);

		void async_upload_from(std::string remote_file, char* buffer_ptr, size_t buffer_size, std::string remote_root = "", std::function<void(bool)> callback = nullptr);
	};
}