#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <sstream>
#include <string>
#include <string_view>

class BaseException: public std::exception
{
public:
    BaseException() = default;
    BaseException(std::string_view msg,
                  std::string_view fileName,
                  std::string_view className,
                  std::string_view methodName,
                  int line = 0) noexcept;

    const char *what() const noexcept override;

protected:
    std::string_view m_msg;
    std::string_view m_fileName;
    std::string_view m_className;
    std::string_view m_methodName;
    std::string m_line;
    std::string m_fullMessage;
};

class InvalidValueException: public BaseException
{
public:
    InvalidValueException(std::string_view fileName,
                          std::string_view className,
                          std::string_view methodName,
                          int line = __LINE__);
};

class UnsupportedTypeTag: public BaseException
{
public:
    UnsupportedTypeTag(std::string_view fileName,
                       std::string_view className,
                       std::string_view methodName,
                       int line = __LINE__);
};

class UnsupportedKeyConfiguration: public BaseException
{
public:
    UnsupportedKeyConfiguration(std::string_view fileName,
                                std::string_view className,
                                std::string_view methodName,
                                int line = __LINE__);
};

class FileException: public BaseException
{
public:
    FileException(std::string_view fileName,
                  std::string_view className,
                  std::string_view methodName,
                  int line = __LINE__);
};

class NoTypeTagException: public BaseException
{
public:
    NoTypeTagException(std::string_view fileName,
                       std::string_view className,
                       std::string_view methodName,
                       int line = __LINE__);
};

class UnsupportedConfiguration: public BaseException
{
public:
    UnsupportedConfiguration(std::string_view fileName,
                             std::string_view className,
                             std::string_view methodName,
                             int line = __LINE__);
};

class MetaSectionError: public BaseException
{
public:
    MetaSectionError(std::string_view fileName,
                     std::string_view className,
                     std::string_view methodName,
                     int line = __LINE__);
};

#endif