#pragma once

#include "exceptions.h"

#include <cstddef>
#include <cstdio>

static size_t EXCEPTION_MESSAGE_SIZE = 100;

BaseException::BaseException(const char *info, const std::source_location &loc) noexcept
{
    snprintf(message, EXCEPTION_MESSAGE_SIZE, "File: %s (%d:%d) `%s`: %s\n", loc.file_name(), loc.line(), loc.column(),
             loc.function_name(), info);
}

const char *BaseException::what() const noexcept
{
    return message;
}

IteratorException::IteratorException(const char *info, const std::source_location &loc) noexcept
    : BaseException(info, loc){};

SetException::SetException(const char *info, const std::source_location &loc) noexcept : BaseException(info, loc){};

MemoryException::MemoryException(const char *info, const std::source_location &loc) noexcept
    : SetException(info, loc){};
