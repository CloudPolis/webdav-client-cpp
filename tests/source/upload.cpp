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