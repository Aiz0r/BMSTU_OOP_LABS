#pragma once

#define EXCEPTION_MESSAGE_SIZE 100

#include <source_location>

#include <exception>

class BaseException : public std::exception
{
protected:
    char message[EXCEPTION_MESSAGE_SIZE];

public:
    BaseException(const char *info,
                  const std::source_location &loc = std::source_location::current()) noexcept;
    virtual const char *what() const noexcept override;
};

class IteratorException : public BaseException
{
public:
    IteratorException(const char *info,
                      const std::source_location &loc = std::source_location::current()) noexcept;
};

class SetException : public BaseException
{
public:
    SetException(const char *info,
                 const std::source_location &loc = std::source_location::current()) noexcept;
};

class MemoryException : public SetException
{
public:
    MemoryException(const char *info,
                    const std::source_location &loc = std::source_location::current()) noexcept;
};

#include "exceptions.hpp"
