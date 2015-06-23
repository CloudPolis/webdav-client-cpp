#pragma once

namespace WebDAV
{
	///
	/// \brief WebDAV client
	/// \author designerror
	/// \version 1.0
	/// \date Март 2015 года
	///
	class Client
	{
		enum { buffer_size = 1000 * 1000 };

		void init() noexcept;

		std::string webdav_hostname;
		std::string webdav_root;
		std::string webdav_login;
		std::string webdav_password;

		std::string proxy_hostname;
		std::string proxy_login;
		std::string proxy_password;

		std::string cert_path;
		std::string key_path;

		std::map<std::string, std::string> options() noexcept;

		bool sync_download(std::string remote_file, std::string local_file, std::function<void(bool)> callback = nullptr) noexcept;
		bool sync_download_to(std::string remote_file, char* & buffer_ptr, long long int & buffer_size, std::function<void(bool)> callback = nullptr) noexcept;

		bool sync_upload(std::string remote_file, std::string local_file, std::function<void(bool)> callback = nullptr) noexcept;
		bool sync_upload_from(std::string remote_file, char* buffer_ptr, long long int buffer_size, std::function<void(bool)> callback = nullptr) noexcept;


	public:

		///
		/// \param[in] webdav_hostname
		/// \param[in] webdav_root
		/// \param[in] webdav_login
		/// \param[in] webdav_password
		/// \param[in] proxy_hostname
		/// \param[in] proxy_login
		/// \param[in] proxy_password
		/// \param[in] cert_path
		/// \param[in] key_path
		/// \include client/init.cpp
		///
		Client(std::map<std::string, std::string> & options) noexcept;

		~Client() noexcept;

		///
		/// Get free size of the WebDAV server
		/// \return size in bytes
		/// \include client/size.cpp
		///
		long long free_size() noexcept;

		///
		/// Check for existence of a remote resource
		/// \param[in] remote_resource
		/// \include client/check.cpp
		///
		bool check(std::string remote_resource = "/") noexcept;

		///
		/// Get information of a remote resource
		/// \param[in] remote_resource
		/// \include client/info.cpp
		///
		std::map<std::string, std::string> info(std::string remote_resource) noexcept;

		///
		/// Clean an remote resource
		/// \param[in] remote_resource
		/// \include client/clean.cpp
		///
		bool clean(std::string remote_resource) noexcept;

		///
		/// Checks whether the resource directory
		/// \param[in] remote_resource
		///
		bool is_dir(std::string remote_resource) noexcept;

		///
		/// List a remote directory
		/// \param[in] remote_directory
		/// \include client/list.cpp
		///
		std::vector<std::string> list(std::string remote_directory = "") noexcept;

		///
		/// Create a remote directory
		/// \param[in] remote_directory
		/// \param[in] recursive
		/// \include client/mkdir.cpp
		///
		bool create_directory(std::string remote_directory, bool recursive = false) noexcept;

		///
		/// Move a remote resource
		/// \param[in] remote_source_resource
		/// \param[in] remote_destination_resource
		/// \include client/move.cpp
		///
		bool move(std::string remote_source_resource, std::string remote_destination_resource) noexcept;

		///
		/// Copy a remote resource
		/// \param[in] remote_source_resource
		/// \param[in] remote_destination_resource
		/// \include client/copy.cpp
		///
		bool copy(std::string remote_source_resource, std::string remote_destination_resource) noexcept;

		///
		/// Download a remote file to a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \snippet client/download.cpp download_to_file
		///
		bool download(std::string remote_file, std::string local_file) noexcept;

		///
		/// Download a remote file to a buffer
		/// \param[in] remote_file
		/// \param[out] buffer_ptr
		/// \param[out] buffer_size
		/// \snippet client/download.cpp download_to_buffer
		///
		bool download_to(std::string remote_file, char* & buffer_ptr, long long int & buffer_size) noexcept;

		///
		/// Asynchronously download a remote file to a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] callback
		/// \snippet client/download.cpp async_download_to_file
		///
		void async_download(std::string remote_file, std::string local_file, std::function<void(bool)> callback = nullptr) noexcept;

		///
		/// Asynchronously download a remote file to a buffer
		/// \param[in] remote_file
		/// \param[out] buffer_ptr
		/// \param[out] buffer_size
		/// \param[in] callback
		/// \snippet client/download.cpp async_download_to_buffer
		///
		void async_download_to(std::string remote_file, char* & buffer_ptr, long long int & buffer_size, std::function<void(bool)> callback = nullptr) noexcept;

		///
		/// Upload a remote file from a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \snippet client/upload.cpp upload_from_file
		///
		bool upload(std::string remote_file, std::string local_file) noexcept;

		///
		/// Upload a remote file from a buffer
		/// \param[in] remote_file
		/// \param[in] buffer_ptr
		/// \param[in] buffer_size
		/// \snippet client/upload.cpp upload_from_buffer
		///
		bool upload_from(std::string remote_file, char* buffer_ptr, long long int buffer_size) noexcept;

		///
		/// Asynchronously upload a remote file from a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] callback
		/// \snippet client/upload.cpp async_upload_from_file
		///
		void async_upload(std::string remote_file, std::string local_file, std::function<void(bool)> callback = nullptr) noexcept;

		///
		/// Asynchronously upload a remote file from a buffer
		/// \param[in] remote_file
		/// \param[in] buffer_ptr
		/// \param[in] buffer_size
		/// \param[in] callback
		/// \snippet client/upload.cpp async_upload_from_buffer
		///
		void async_upload_from(std::string remote_file, char* buffer_ptr, long long int buffer_size, std::function<void(bool)> callback = nullptr) noexcept;
	};
}
