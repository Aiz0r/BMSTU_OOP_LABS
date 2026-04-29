#pragma once

#include "base_exceptions.h"

#include <cstdio>


BaseException::BaseException(const char *info, const std::source_location &loc) noexcept
{
    std::snprintf(message.data(), MESSAGE_SIZE, "Exception %s at %s:%d", info, loc.file_name(), loc.line());
}

const char *BaseException::what() const noexcept
{
    return message.data();
}
