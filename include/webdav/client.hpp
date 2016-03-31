#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace WebDAV
{
	typedef std::function<int(	void *context,
								size_t dltotal,
								size_t dlnow, 
								size_t ultotal, 
								size_t ulnow)> progress_t;

	typedef std::function<void(bool)> callback_t;

	using strings_t = std::vector<std::string>;
	using dict_t  = std::map<std::string, std::string>;

	///
	/// \brief WebDAV Client
	/// \author designerror
	/// \version 1.1.0
	/// \date 29/01/2016
	///
	class Client
	{	
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
		static Client * Init(dict_t & options) noexcept;

		~Client() noexcept;

		///
		/// Get free size of the WebDAV server
		/// \return size in bytes
		/// \include client/size.cpp
		///
		auto free_size() noexcept -> unsigned long long;

		///
		/// Check for existence of a remote resource
		/// \param[in] remote_resource
		/// \include client/check.cpp
		///
		auto check(std::string remote_resource = "/") noexcept -> bool;

		///
		/// Get information of a remote resource
		/// \param[in] remote_resource
		/// \include client/info.cpp
		///
		auto info(std::string remote_resource) noexcept -> dict_t;

		///
		/// Clean an remote resource
		/// \param[in] remote_resource
		/// \include client/clean.cpp
		///
		auto clean(std::string remote_resource) noexcept -> bool;

		///
		/// Checks whether the resource directory
		/// \param[in] remote_resource
		///
		auto is_dir(std::string remote_resource) noexcept -> bool;

		///
		/// List a remote directory
		/// \param[in] remote_directory
		/// \include client/list.cpp
		///
		auto list(std::string remote_directory = "") noexcept -> strings_t;

		///
		/// Create a remote directory
		/// \param[in] remote_directory
		/// \param[in] recursive
		/// \include client/mkdir.cpp
		///
		auto create_directory(
			std::string remote_directory, 
			bool recursive = false
		) noexcept -> bool;

		///
		/// Move a remote resource
		/// \param[in] remote_source_resource
		/// \param[in] remote_destination_resource
		/// \include client/move.cpp
		///
		auto move(
			std::string remote_source_resource, 
			std::string remote_destination_resource
		) noexcept -> bool;

		///
		/// Copy a remote resource
		/// \param[in] remote_source_resource
		/// \param[in] remote_destination_resource
		/// \include client/copy.cpp
		///
		auto copy(
			std::string remote_source_resource, 
			std::string remote_destination_resource
		) noexcept -> bool;

		///
		/// Download a remote file to a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] progress
		/// \snippet client/download.cpp download_to_file
		///
		auto download(
			std::string remote_file, 
			std::string local_file, 
			progress_t progress = nullptr
		) noexcept -> bool;

		///
		/// Download a remote file to a buffer
		/// \param[in] remote_file
		/// \param[out] buffer_ptr
		/// \param[out] buffer_size
		/// \param[in] progress
		/// \snippet client/download.cpp download_to_buffer
		///
		auto download_to(
			std::string remote_file,
			char * & buffer_ptr, 
			unsigned long long int & buffer_size, 
			progress_t progress = nullptr
		) noexcept -> bool;

		///
		/// Download a remote file to a stream
		/// \param[in] remote_file
		/// \param[out] stream
		/// \param[in] progress
		/// \snippet client/download.cpp download_to_stream
		///
		auto download_to(
			std::string remote_file,
			std::ostream & stream,
			progress_t progress = nullptr
		) noexcept -> bool;

		///
		/// Asynchronously download a remote file to a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] callback
		/// \param[in] progress
		/// \snippet client/download.cpp async_download_to_file
		///
		auto async_download(
			std::string remote_file, 
			std::string local_file, 
			callback_t callback = nullptr, 
			progress_t progress = nullptr
		) noexcept -> void;

		///
		/// Upload a remote file from a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] progress
		/// \snippet client/upload.cpp upload_from_file
		///
		auto upload(
			std::string remote_file,
			std::string local_file, 
			progress_t progress = nullptr
		) noexcept -> bool;

		///
		/// Upload a remote file from a buffer
		/// \param[in] remote_file
		/// \param[in] buffer_ptr
		/// \param[in] buffer_size
		/// \param[in] progress
		/// \snippet client/upload.cpp upload_from_buffer
		///
		auto upload_from(
			std::string remote_file, 
			char * buffer_ptr, 
			unsigned long long int buffer_size, 
			progress_t progress = nullptr
		) noexcept -> bool;

		///
		/// Upload a remote file from a stream
		/// \param[in] remote_file
		/// \param[in] stream
		/// \param[in] progress
		/// \snippet client/upload.cpp upload_from_stream
		///
		auto upload_from(
			std::string remote_file, 
			std::istream & stream, 
			progress_t progress = nullptr
		) noexcept -> bool;

		///
		/// Asynchronously upload a remote file from a local file
		/// \param[in] remote_file
		/// \param[in] local_file
		/// \param[in] callback
		/// \param[in] progress
		/// \snippet client/upload.cpp async_upload_from_file
		///
		auto async_upload(
			std::string remote_file, 
			std::string local_file, 
			callback_t callback = nullptr,
			progress_t progress = nullptr
		) noexcept -> void;

	protected:

		enum { buffer_size = 1000 * 1000 };

		Client() {}
	};
}
