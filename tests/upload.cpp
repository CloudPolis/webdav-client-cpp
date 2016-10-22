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

#include "stdafx.h"
#include "catch.hpp"

SCENARIO("Client must upload buffer", "[upload][buffer]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("A buffer") {

		std::string buffer = "content of the buffer";
		std::string remote_resource = "file.dat";

		auto buffer_pointer = const_cast<char *>(buffer.c_str());
		auto buffer_size = buffer.length() * sizeof(buffer.c_str()[0]);

		WHEN("Upload the buffer") {

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

SCENARIO("Client must upload stream", "[upload][string][stream]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("A stream") {

		std::stringstream stream("content of the stream");
		std::string remote_resource = "file.dat";

		WHEN("Upload the stream") {

			REQUIRE(client->clean(remote_resource));
			REQUIRE(!client->check(remote_resource));

			auto is_success = client->upload_from(remote_resource, stream);

			THEN("stream must be uploaded") {

				CHECK(is_success);
				CHECK(client->check(remote_resource));
			}
		}
	}
}  

SCENARIO("Client must upload file stream", "[upload][file][stream]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("A stream") {

		std::fstream stream("C:\\Users\\host\\Downloads\\libyaml-master.zip", std::ios::binary | std::ios::in | std::ios::out);
		std::string remote_resource = "libyaml-master.zip";

		WHEN("Upload the stream") {

			REQUIRE(client->clean(remote_resource));
			REQUIRE(!client->check(remote_resource));

			auto is_success = client->upload_from(remote_resource, stream);

			THEN("stream must be uploaded") {

				CHECK(is_success);
				CHECK(client->check(remote_resource));
			}
		}
	}
}  