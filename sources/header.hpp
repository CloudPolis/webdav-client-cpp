#ifndef WEBDAV_HEADER_H
#define WEBDAV_HEADER_H
#pragma once

namespace WebDAV
{
    class Header final
    {
    public:
        void * handle;

        Header(std::initializer_list<std::string> init_list) noexcept;
        ~Header();

        void append(const std::string item) noexcept;
    };
}

#endif
