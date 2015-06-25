#include "stdafx.h"
#include <catch.hpp>

SCENARIO("Client must list a remote files and a remote directories", "[list]") {

  std::unique_ptr<WebDAV::Client> client(new WebDAV::Client(options));

  GIVEN("A remote directory with 5 files and 5 directories") {

    std::string root = "dir_with_files_and_dirs/";

    std::string template_filename = "file";
    std::string template_dirname = "dir";

    CHECK(client->clean(root));
    REQUIRE(client->create_directory(root));

    for (auto i = 1; i <= 5; ++i)
    {
      auto number = std::to_string(i);
      auto directory = root + template_dirname + number;
      auto file = root + template_filename + number;
      client->create_directory(directory);
      client->upload_from(file, (char *)file_content.c_str(), file_content.length());
    }

    WHEN("List the directory") {

      auto resources = client->list(root);

      THEN("Get 10 resources") {

        CHECK(resources.size() == 10);
      }
    }
  }
}

SCENARIO("Client can not list a remote file", "[list][file]") {

  std::unique_ptr<WebDAV::Client> client(new WebDAV::Client(options));

  GIVEN("An existing remote file") {

    std::string existing_file = "file.dat";

    client->upload_from(existing_file, (char *)file_content.c_str(), file_content.length());

    WHEN("List content of the file") {

      REQUIRE(client->check(existing_file));

      auto resources = client->list(existing_file);

      THEN("Get an empty list") {

        CHECK(resources.empty());
      }
    }
  }
}

SCENARIO("Client can list an empty remote directory", "[list][empty]") {

  std::unique_ptr<WebDAV::Client> client(new WebDAV::Client(options));

    GIVEN("An empty remote directory") {

    std::string empty_directory = "empty_directory/";

    client->create_directory(empty_directory);

    WHEN("List content of the directory") {

      REQUIRE(client->check(empty_directory));

      auto resources = client->list(empty_directory);

      THEN("Get an empty list") {

        CHECK(resources.empty());
      }
    }
  }
}