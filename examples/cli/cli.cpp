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
#include <exception>

using dict_t = std::map<std::string, std::string>;
using strings_t = std::vector<std::string>;

auto operator<<(std::ostream& out, const dict_t& dict) -> std::ostream&
{
  for (auto& item : dict)
  {
    out << item.first << ": " << item.second << std::endl;
  }
  return out;
}

auto operator<<(std::ostream& out, const strings_t& dict) -> std::ostream&
{
  for (auto& item : dict)
  {
    out << "- " << item << std::endl;
  }
  return out;
}

int main(int argc, char* argv[])
{

  try
  {

    auto hostname_ptr = std::getenv("WEBDAV_HOSTNAME");
    auto username_ptr = std::getenv("WEBDAV_USERNAME");
    auto password_ptr = std::getenv("WEBDAV_PASSWORD");
    auto root_ptr = std::getenv("WEBDAV_ROOT");

    if (hostname_ptr == nullptr)
    {
      throw std::runtime_error("undefined WEBDAV_HOSTNAME environment variable");
    }
    if (username_ptr == nullptr)
    {
      throw std::runtime_error("undefined WEBDAV_USERNAME environment variable");
    }
    if (password_ptr == nullptr)
    {
      throw std::runtime_error("undefined WEBDAV_PASSWORD environment variable");
    }

    if (argc < 2)
    {
      throw std::invalid_argument("command");
    }

    if (argc < 3)
    {
      throw std::invalid_argument("resource");
    }

    std::string command = argv[1];
    std::string remote_resource = argv[2];

    std::map<std::string, std::string> options =
    {
      {"webdav_hostname", hostname_ptr},
      {"webdav_username", username_ptr},
      {"webdav_password", password_ptr}
    };

    if (root_ptr != nullptr)
    {
      options["webdav_root"] = root_ptr;
    }

    std::unique_ptr<WebDAV::Client> client{ new WebDAV::Client{ options } };

    if (command == "check")
    {
      bool is_existed = client->check(remote_resource);
      std::cout << "Resource: " << remote_resource << " is " << (is_existed ? "" : "not ") << "existed"
                << std::endl;
    }
    else if (command == "copy")
    {
      if (argc < 4)
      {
        throw std::invalid_argument("to");
      }
      std::string target_resource = argv[3];
      client->copy(remote_resource, target_resource);
    }
    else if (command == "download")
    {
      if (argc < 4)
      {
        throw std::invalid_argument("to");
      }
      std::string target_resource = argv[3];
      client->download(remote_resource, target_resource);
    }
    else if (command == "info")
    {
      auto info = client->info(remote_resource);
      std::cout << info << std::endl;
    }
    else if (command == "list")
    {
      auto list = client->list(remote_resource);
      std::cout << list << std::endl;
    }
    else if (command == "mkdir")
    {
      client->create_directory(remote_resource);
    }
    else if (command == "move")
    {
      if (argc < 4)
      {
        throw std::invalid_argument("to");
      }
      std::string target_resource = argv[3];
      client->move(remote_resource, target_resource);
    }
    else if (command == "remove")
    {
      client->clean(remote_resource);
    }
    else if (command == "upload")
    {
      if (argc < 4)
      {
        throw std::invalid_argument("from");
      }
      std::string target_resource = argv[3];
      client->upload(remote_resource, target_resource);
    }
  }
  catch (std::invalid_argument& error)
  {
    std::cout << "use: <command> <resource> [<from|to>]" << std::endl;
  }
  catch (std::runtime_error& error)
  {
    std::cout << error.what() << std::endl;
  }
}
