/*#***************************************************************************
#                         __    __   _____       _____
#   Project              |  |  |  | |     \     /  ___|
#                        |  |__|  | |  |\  \   /  /
#                        |        | |  | )  ) (  (
#                        |   /\   | |  |/  /   \  \___
#                         \_/  \_/  |_____/     \_____|
#
# Copyright (C) 2018, The WDC Project, <rusdevops@gmail.com>, et al.
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

#include "fixture.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <map>
#include <string>
#include <cstdlib>

using dict_t = std::map<std::string, std::string>;

std::string file_ext = ".txt";
std::string file_content = "static std::wstring file_content = L\"static std::wstring file_content = ...\";";
std::string buff_content = "static std::wstring buff_content = L\"static std::wstring buff_content = ...\";";

namespace fixture
{
  auto get_file_content() -> std::string
  {
    return file_content;
  }

  auto get_buff_content() -> std::string
  {
    return buff_content;
  }

  auto get_file_name() -> std::string
  {
    boost::uuids::random_generator gen;
    boost::uuids::uuid id = gen();
    auto ciid = to_string(id);
    return ciid + file_ext;;
  }

  auto get_dir_name() -> std::string
  {
    boost::uuids::random_generator gen;
    boost::uuids::uuid id = gen();
    auto ciid = to_string(id);
    return ciid + "/";
  }

  auto get_options() -> dict_t
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

    std::map<std::string, std::string> options =
    {
      {"webdav_hostname", hostname_ptr},
      {"webdav_username",    username_ptr},
      {"webdav_password", password_ptr}
    };

    if (root_ptr != nullptr)
    {
      options["webdav_root"] = root_ptr;
    }

    const auto proxy_hostname_ptr = std::getenv("PROXY_HOSTNAME");
    const auto proxy_username_ptr = std::getenv("PROXY_USERNAME");
    const auto proxy_password_ptr = std::getenv("PROXY_PASSWORD");

    if (proxy_hostname_ptr != nullptr)
    {
      options["proxy_hostname"] = proxy_hostname_ptr;
    }
    if (proxy_username_ptr != nullptr)
    {
      options["proxy_username"] = proxy_username_ptr;
    }
    if (proxy_password_ptr != nullptr && proxy_username_ptr != nullptr)
    {
      options["proxy_password"] = proxy_password_ptr;
    }
    return options;
  }
}
