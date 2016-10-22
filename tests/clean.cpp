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

SCENARIO("Client must clean an existing remote resources", "[clean]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("An existing remote resource") {

		std::string existing_file = "file.dat";
		std::string existing_directory = "existing_directory/";

		client->upload_from(existing_file, (char *)file_content.c_str(), file_content.length());
		client->create_directory(existing_directory);

		WHEN("Clean an existing remote file") {

			REQUIRE(client->check(existing_file));

			auto is_success = client->clean(existing_file);

			THEN("The file is cleaning") {

				CHECK(is_success);
				CHECK_FALSE(client->check(existing_file));
			}
		}

		WHEN("Clean an existing directory") {

			REQUIRE(client->check(existing_directory));

			auto is_success = client->clean(existing_directory);

			THEN("The directory is cleaning") {

				CHECK(is_success);
				CHECK_FALSE(client->check(existing_directory));
			}
		}
	}
}

SCENARIO("Client must clean not an existing remote resources", "[clean]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("Not an existing remote resource") {

		std::string not_existing_file = "not_existing_file.dat";
		std::string not_existing_directory = "not_existing_directory/";

		WHEN("Clean not an existing remote file") {

			REQUIRE_FALSE(client->check(not_existing_file));

			auto is_success = client->clean(not_existing_file);

			THEN("The file is cleaning") {

				CHECK(is_success);
				CHECK_FALSE(client->check(not_existing_file));
			}
		}

		WHEN("Clean not an existing directory") {

			REQUIRE_FALSE(client->check(not_existing_directory));

			auto is_success = client->clean(not_existing_directory);

			THEN("The directory is cleaning") {

				CHECK(is_success);
				CHECK_FALSE(client->check(not_existing_directory));
			}
		}
	}
}

SCENARIO("Client must clean not an empty remote directories", "[clean]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("Not an empty remote directory") {

		std::string not_empty_directory = "not_empty_directory/";
		std::string attached_file = "not_empty_directory/attached_file.dat";
		std::string attached_directory = "not_empty_directory/attached_directory/";

		client->create_directory(not_empty_directory);
		client->upload_from(attached_file, (char *)file_content.c_str(), file_content.length());
		client->create_directory(attached_directory);

		WHEN("Clean not an empty directory") {

			REQUIRE(client->check(not_empty_directory));
			REQUIRE(client->check(attached_file));
			REQUIRE(client->check(attached_directory));

			auto is_success = client->clean(not_empty_directory);

			REQUIRE(is_success);

			THEN("The directory and the attached resources are cleaning") {

				CHECK_FALSE(client->check(not_empty_directory));
				CHECK_FALSE(client->check(attached_file));
				CHECK_FALSE(client->check(attached_directory));
			}
		}
	}
}

SCENARIO("Client must clean a remote directory", "[clean]") {

	std::unique_ptr<WebDAV::Client> client(WebDAV::Client::Init(options));

	GIVEN("An existing directory") {
		
		std::string directory_name = "directory";	
		client->create_directory(directory_name);

		WHEN("Clean directory by a name") {

			REQUIRE(client->check(directory_name));

			auto is_success = client->clean(directory_name);

			THEN("The directory is cleaning") {

				CHECK_FALSE(client->check(directory_name));
			}
		}
	}
}