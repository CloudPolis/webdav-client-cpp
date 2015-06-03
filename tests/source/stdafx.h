#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

#ifndef _MSC_VER
#define noexcept noexcept
#else
#define noexcept
#endif

#include <client.hpp>
#include "config.hpp"
