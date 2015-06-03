#pragma once

namespace WebDAV
{
    class Header
    {
    public:

        void * handle;

        Header(std::initializer_list<std::string> init_list) noexcept;
        ~Header() noexcept;

        void append(std::string item) noexcept;
    };
}