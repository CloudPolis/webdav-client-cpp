WebDAV Client
===
[![version](https://img.shields.io/badge/version-1.0.1-brightgreen.svg)](https://github.com/designerror/webdav-client-cpp/releases/tag/v1.0.1)
[![Gitter](https://badges.gitter.im/designerror/webdav-client-cpp.svg)](https://gitter.im/designerror/webdav-client-cpp?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Build Status](https://travis-ci.org/designerror/webdav-client-cpp.svg?branch=v0.9.9)](https://travis-ci.org/designerror/webdav-client-cpp)
[![Build status](https://ci.appveyor.com/api/projects/status/l0nwebsyxwcc3lcs?svg=true)](https://ci.appveyor.com/project/designerror/webdav-client-cpp)

Package ```WebDAV Client``` provides easy and convenient to work with WebDAV-servers:

 - Yandex.Disk
 - Dropbox
 - Google Drive
 - Box
 - 4shared
 - ...

Requirements
===

 - [curl](https://github.com/curl/curl) `>= 7.38.0`
 - [openssl](https://github.com/openssl/openssl) `>= 1.0.1f`
 - [pugixml](https://github.com/zeux/pugixml) `>= 1.0.0`

Install
===

For `Windows` see `INSTALL.WIN.md` file.

**Building requirements**

For `*-nix` or `macOS` you can build the requirements with package manager or from sources.

If you want to build the requirements from sources then see `INSTALL.UNIX.md` and `INSTALL.macOS.md` respectively.

If you want to use package manager then input:

```bash
# Debian or Ubuntu
$ sudo apt-get install libssl-dev libcurl4-openssl-dev libpugixml-dev

# Fedora
$ sudo dnf install openssl-devel curl-devel pugixml-devel

# macOS
$ brew install curl pugixml
```

**Building WebDAV Client**

```bash
$ git clone https://github.com/designerror/webdav-client-cpp
$ cd webdav-client-cpp
$ mkdir build && cd build
# The next line is needed for building on macOS
$ export OPENSSL_ROOT_DIR=/usr/local/opt/openssl/
$ cmake .. && make
$ make install
```

Documentation
===

```bash
$ cd docs
$ doxygen doxygen.conf
$ firefox html/index.html
```

Usage examples
===

```c++
#include <iostream>
#include <memory>
#include <webdav/client.hpp>

int main()
{
  std::map<std::string, std::string> options =
  {
      {"webdav_hostname", "https://webdav.yandex.ru"},
      {"webdav_login",    "webdav_login"},
      {"webdav_password", "webdav_password"}
  };
  // additional keys: 
  // - webdav_root
  // - cert_path, key_path
  // - proxy_hostname, proxy_login, proxy_password
            
  std::shared_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));
  
  auto check_connection = client->check();
  std::cout << "test connection with WebDAV drive is " 
            << (check_connection ? "" : "not ")
            << "successful"<< std::endl;
  
  auto is_directory = client->is_dir("/path/to/remote/resource");
  std::cout << "remote resource is " 
            << (is_directory ? "" : "not ") 
            << "directory" << std::endl;
  
  client->create_directory("/path/to/remote/directory/");
  client->clean("/path/to/remote/directory/");
  
  std::cout << "On WebDAV-disk available free space: " 
            << client->free_size() 
            << std::endl;
  
  std::cout << "remote_directory_name";
  for(auto& resource_name : client->list("/path/to/remote/directory/"))
  {
      std::cout << "\t" << "-" << resource_name;
  }
  std::cout << std::endl;
  
  client->download("/path/to/remote/file", "/path/to/local/file");
  client->clean("/path/to/remote/file");
  client->upload("/path/to/remote/file", "/path/to/local/file");
  
  auto meta_info = client->info("/path/to/remote/resource");
  for(auto& field : meta_info)
  {
      std::cout << field.first << ":" << "\t" << field.second;
  }
  std::cout << std::endl;

  client->copy("/path/to/remote/file1", "/path/to/remote/file2");
  client->move("/path/to/remote/file1", "/path/to/remote/file3");
  
  client->async_upload("/path/to/remote/file", "/path/to/local/file");
  client->async_download("/path/to/remote/file", "/path/to/local/file");
}
```

Soon
===
```bash
# via apt
$ sudo apt install libwdc-dev

# via dnf
$ sudo dnf install wdc-devel

# via yum
$ yum install wdc
```

Until
===
```bash
# via homebrew or linuxbrew
$ brew install wdc
```

