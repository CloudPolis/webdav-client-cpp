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

#include <webdav/client.hpp>

#include "fixture.hpp"

#include <catch.hpp>

#include <fstream>
#include <memory>
#include <sstream>

SCENARIO("Client must upload buffer", "[upload][buffer]")
{
  auto options = fixture::get_options();
  auto content = fixture::get_buff_content();
  auto filename = fixture::get_file_name();

  CAPTURE(filename);

  std::unique_ptr<WebDAV::Client> client{ new WebDAV::Client{ options } };

  GIVEN("A buffer")
  {
    std::string remote_resource = filename;

    auto buffer_pointer = const_cast<char *>(content.c_str());
    auto buffer_size = content.length() * sizeof(content.c_str()[0]);

    WHEN("Upload the buffer")
    {
      REQUIRE(client->clean(remote_resource));
      REQUIRE(!client->check(remote_resource));

      auto is_success = client->upload_from(remote_resource, buffer_pointer, buffer_size);

      THEN("buffer must be uploaded") {

        CHECK(is_success);
        CHECK(client->check(remote_resource));
      }
    }
  }
}

SCENARIO("Client must upload string stream", "[upload][string][stream]")
{
  auto options = fixture::get_options();
  auto content = fixture::get_buff_content();
  auto filename = fixture::get_file_name();

  CAPTURE(filename);

  std::unique_ptr<WebDAV::Client> client{ new WebDAV::Client{ options } };

  GIVEN("A stream")
  {
    std::stringstream stream(content);
    std::string remote_resource = filename;

    WHEN("Upload the stream")
    {
      REQUIRE(client->clean(remote_resource));
      REQUIRE(!client->check(remote_resource));

      auto is_success = client->upload_from(remote_resource, stream);

      THEN("stream must be uploaded")
      {
        CHECK(is_success);
        CHECK(client->check(remote_resource));
      }
    }
  }
}

SCENARIO("Client must upload file stream", "[upload][file][stream]")
{
  auto options = fixture::get_options();
  auto content = fixture::get_file_content();
  auto filename = fixture::get_file_name();

  CAPTURE(filename);

  std::unique_ptr<WebDAV::Client> client{ new WebDAV::Client{ options } };

  GIVEN("A stream")
  {
    std::ofstream out(filename);
    out << content;

    std::ifstream in(filename, std::ios::binary);
    std::string remote_resource = filename;

    WHEN("Upload the stream")
    {
      REQUIRE(client->clean(remote_resource));
      REQUIRE(!client->check(remote_resource));

      auto is_success = client->upload_from(remote_resource, in);

      THEN("stream must be uploaded")
      {
        CHECK(is_success);
        CHECK(client->check(remote_resource));
      }
    }
  }
}
