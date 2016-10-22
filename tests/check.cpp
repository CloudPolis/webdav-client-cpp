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

SCENARIO("Client must check an existing remote resources", "[check]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("An existing remote resource") {

		std::string existing_file = "file.dat";
		std::string existing_directory = "dir/";

		client->upload_from(existing_file, (char *)file_content.c_str(), file_content.length());
		client->create_directory(existing_directory);

		WHEN("Check for existence of an existing remote file") {

			REQUIRE(client->check(existing_file));

			auto is_success = client->check(existing_file);

			THEN("Check must be success") {

				CHECK(is_success);
			}
		}

		WHEN("Check for existence of an existing remote directory") {

			REQUIRE(client->check(existing_directory));

			auto is_success = client->check(existing_directory);

			THEN("The directory is cleaning") {

				CHECK(is_success);
			}
		}
	}
}

SCENARIO("Client must check not an existing remote resources", "[check]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("Not an existing remote resource") {

		std::string not_existing_file = "not_existing_file.dat";
		std::string not_existing_directory = "not_existing_directory/";

		WHEN("Check for existence of not an existing remote file") {

			REQUIRE(client->clean(not_existing_file));

			auto is_success = client->check(not_existing_file);

			THEN("Check must be not success") {

				CHECK_FALSE(is_success);
			}
		}

		WHEN("Check for existence of an existing remote directory") {

			REQUIRE(client->clean(not_existing_directory));

			auto is_success = client->check(not_existing_directory);

			THEN("Check must be not success") {

				CHECK_FALSE(is_success);
			}
		}
	}
}