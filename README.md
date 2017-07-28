WebDAV Client
===
[![version](https://img.shields.io/badge/hunter-v0.19.51-blue.svg)](https://github.com/ruslo/hunter/tree/v0.19.51)
[![version](https://img.shields.io/badge/wdc-v1.0.9-blue.svg)](https://github.com/CloudPolis/webdav-client-cpp/releases/tag/v1.0.9)
[![Build Status](https://travis-ci.org/CloudPolis/webdav-client-cpp.svg?branch=master)](https://travis-ci.org/CloudPolis/webdav-client-cpp)
[![Build status](https://ci.appveyor.com/api/projects/status/cr2xwpwe3iiafbwg?svg=true)](https://ci.appveyor.com/project/rusdevops/webdav-client-cpp)
[![Join the chat at https://gitter.im/CloudPolis/webdav-client-cpp](https://badges.gitter.im/CloudPolis/webdav-client-cpp.svg)](https://gitter.im/CloudPolis/webdav-client-cpp?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Package ```WebDAV Client``` provides easy and convenient to work with WebDAV-servers:

 - Yandex.Disk
 - Dropbox
 - Google Drive
 - Box
 - 4shared
 - ...

Install
===

```ShellSession
# via brew or homebrew
$ brew install wdc
```

Build
===

Building WebDAV Client from sources:

```ShellSession
$ git clone https://github.com/designerror/webdav-client-cpp
$ cd webdav-client-cpp
$ cmake -H. -B_builds # -DCMAKE_INSTALL_PREFIX=install
$ cmake --build _builds
$ cmake --build _builds --target install
```

Documentation
===

```ShellSession
$ cd docs
$ doxygen doxygen.conf
$ open html/index.html
```

Usage
===

**example.cpp**
```C++
#include <iostream>
#include <memory>
#include <webdav/client.hpp>

int main()
{
	std::map<std::string, std::string> options =
	{
		{"webdav_hostname", "https://webdav.yandex.ru"},
		{"webdav_username", "webdav_username"},
		{"webdav_password", "webdav_password"}
	};
	// additional keys: 
	// - webdav_root
	// - cert_path, key_path
	// - proxy_hostname, proxy_username, proxy_password
            
	std::shared_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
  
	auto check_connection = client->check();
	std::cout   << "test connection with WebDAV drive is " 
                    << (check_connection ? "" : "not ")
                    << "successful"<< std::endl;
  
	auto is_dir = client->is_directory("/path/to/remote/resource");
	std::cout   << "remote resource is " 
                    << (is_dir ? "" : "not ") 
                    << "directory" << std::endl;
  
  	client->create_directory("/path/to/remote/directory/");
  	client->clean("/path/to/remote/directory/");
  
  	std::cout   << "On WebDAV-disk available free space: " 
                    << client->free_size() 
                    << std::endl;
  
	std::cout << "remote_directory_name";
	for(auto& resource_name : client->list("/path/to/remote/directory/")) {
		std::cout << "\t" << "-" << resource_name;
  	}
  	std::cout << std::endl;
  
  	client->download("/path/to/remote/file", "/path/to/local/file");
  	client->clean("/path/to/remote/file");
  	client->upload("/path/to/remote/file", "/path/to/local/file");
  
  	auto meta_info = client->info("/path/to/remote/resource");
  	for(auto& field : meta_info) {
		std::cout << field.first << ":" << "\t" << field.second;
  	}
  	std::cout << std::endl;

  	client->copy("/path/to/remote/file1", "/path/to/remote/file2");
  	client->move("/path/to/remote/file1", "/path/to/remote/file3");
  
  	client->async_upload("/path/to/remote/file", "/path/to/local/file");
  	client->async_download("/path/to/remote/file", "/path/to/local/file");
}
```

**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.3)

include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.19.51.tar.gz"
    SHA1 "d238dc1dd4db83e45a592f96fdb95d17c688600a"
)

project(example)

hunter_add_package(WDC)
find_package(WDC CONFIG REQUIRED)

add_executable(example example.cpp)
target_link_libraries(example WDC::libwdc)
```
