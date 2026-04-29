#pragma once

#include <source_location>
#include "base_exceptions.h"
#include <exception>

class IteratorException : public BaseException
{
  public:
    IteratorException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class SetException : public BaseException
{
  public:
    SetException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class MemoryException : public SetException
{
  public:
    MemoryException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

#include "exceptions.hpp"
