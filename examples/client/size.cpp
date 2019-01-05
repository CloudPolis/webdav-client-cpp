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

int main()
{

  std::map<std::string, std::string> options =
  {
    { "webdav_hostname", "https://webdav.yandex.ru" },
    { "webdav_username", "{webdav_username}" },
    { "webdav_password", "{webdav_password}" }
  };

  std::unique_ptr<WebDAV::Client> client{ new WebDAV::Client{ options } };

  auto free_size = client->free_size();
  std::cout << "Free size: " << free_size << " bytes" << std::endl;
}

/// Free size: 8234213123 bytes
