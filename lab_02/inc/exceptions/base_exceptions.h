#pragma once

#include <array>
#include <exception>
#include <source_location>

class BaseException : public std::exception
{
    static constexpr size_t MESSAGE_SIZE = 256;
    std::array<char, MESSAGE_SIZE> message;

public:
    BaseException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
    const char *what() const noexcept override;
};

#include "base_exceptions.hpp"
