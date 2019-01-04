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

#include <webdav/client.hpp>

#include <memory>
#include <sstream>
#include <string>
#include <vector>

std::string resources_to_string(const std::vector<std::string>& resources)
{
  std::stringstream result;
  for (const auto& resource : resources)
  {
    result << "\t" << "- " << resource << std::endl;
  }
  return result.str();
}

int main()
{
  auto hostname_ptr = std::getenv("WEBDAV_HOSTNAME");
  auto username_ptr = std::getenv("WEBDAV_USERNAME");
  auto password_ptr = std::getenv("WEBDAV_PASSWORD");
  auto root_ptr = std::getenv("WEBDAV_ROOT");

  if (hostname_ptr == nullptr) return -1;
  if (username_ptr == nullptr) return -1;
  if (password_ptr == nullptr) return -1;

  std::map<std::string, std::string> options =
  {
      { "webdav_hostname", hostname_ptr },
      { "webdav_username", username_ptr },
      { "webdav_password", password_ptr }
  };

  if (root_ptr != nullptr) {
      options["webdav_root"] = root_ptr;
  }

  std::unique_ptr<WebDAV::Client> client{ new WebDAV::Client{ options } };

  auto remote_file = "file.dat";
  auto remote_directory = "dir/";

  auto copy_remote_file = "file2.dat";
  auto copy_remote_directory = "dir2/";

  auto resources = client->list();
  std::cout << "\"/\" resource contain:" << std::endl;
  std::cout << resources_to_string(resources) << std::endl;

  client->copy(remote_file, copy_remote_file);
  client->copy(remote_directory, copy_remote_directory);

  resources = client->list();

  std::cout << "\"/\" resource contain:" << std::endl;
  std::cout << resources_to_string(resources) << std::endl;
}

/// "/" resource contain:
/// - dir/
/// - file.dat
///
/// "/" resource contain:
/// - dir/
/// - dir2/
/// - file.dat
/// - file2.dat
