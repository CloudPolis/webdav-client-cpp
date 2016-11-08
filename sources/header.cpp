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

#include "header.hpp"

#include <curl/curl.h>

namespace WebDAV
{
    Header::Header(const std::initializer_list<std::string>& init_list) noexcept : handle(nullptr)
    {
        for (auto& item : init_list)
        {
            this->append(item);
        }
    }

    Header::~Header()
    {
        curl_slist_free_all((curl_slist*)this->handle);
    }

    void
    Header::append(const std::string& item) noexcept
    {
        this->handle = curl_slist_append((curl_slist*)this->handle, item.c_str());
    }
}
