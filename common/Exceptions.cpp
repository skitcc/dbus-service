#include "Exceptions.h"
#include <iostream>

#define COLOR_RED "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET "\033[0m"

BaseException::BaseException(std::string_view msg,
                             std::string_view fileName,
                             std::string_view className,
                             std::string_view methodName,
                             int line) noexcept
    : m_msg(msg)
    , m_fileName(fileName)
    , m_className(className)
    , m_methodName(methodName)
    , m_line(std::to_string(line))
{
    std::ostringstream oss;
    oss << "=== EXCEPTION ===\n"
        << "Message: " << m_msg << "\n"
        << "File:    " << m_fileName << "\n"
        << "Class:   " << m_className << "\n"
        << "Method:  " << m_methodName << "\n"
        << "Line:    " << m_line << "\n"
        << "=================\n";
    m_fullMessage = oss.str();
}

const char *BaseException::what() const noexcept
{
    std::cout << COLOR_RED << "=== EXCEPTION ===" << COLOR_RESET << "\n"
              << COLOR_RED << "Message: " << COLOR_RESET << m_msg << "\n"
              << COLOR_YELLOW << "File:    " << COLOR_RESET << m_fileName << "\n"
              << COLOR_YELLOW << "Class:   " << COLOR_RESET << m_className << "\n"
              << COLOR_YELLOW << "Method:  " << COLOR_RESET << m_methodName << "\n"
              << COLOR_YELLOW << "Line:    " << COLOR_RESET << m_line << "\n"
              << COLOR_RED << "=================" << COLOR_RESET << "\n";
    return m_fullMessage.c_str();
}

InvalidValueException::InvalidValueException(std::string_view fileName,
                                             std::string_view className,
                                             std::string_view methodName,
                                             int line)
    : BaseException("Invalid Value in conf file!", fileName, className, methodName, line)
{}

UnsupportedTypeTag::UnsupportedTypeTag(std::string_view fileName,
                                       std::string_view className,
                                       std::string_view methodName,
                                       int line)
    : BaseException("Unsupported type tag!", fileName, className, methodName, line)
{}

UnsupportedKeyConfiguration::UnsupportedKeyConfiguration(std::string_view fileName,
                                                         std::string_view className,
                                                         std::string_view methodName,
                                                         int line)
    : BaseException("Unsupported key!", fileName, className, methodName, line)
{}

FileException::FileException(std::string_view fileName,
                             std::string_view className,
                             std::string_view methodName,
                             int line)
    : BaseException("Error while interacting with file!", fileName, className, methodName, line)
{}

NoTypeTagException::NoTypeTagException(std::string_view fileName,
                                       std::string_view className,
                                       std::string_view methodName,
                                       int line)
    : BaseException("No type tag!", fileName, className, methodName, line)
{}

UnsupportedConfiguration::UnsupportedConfiguration(std::string_view fileName,
                                                   std::string_view className,
                                                   std::string_view methodName,
                                                   int line)
    : BaseException("Unsupported Configuration!", fileName, className, methodName, line)
{}

MetaSectionError::MetaSectionError(std::string_view fileName,
                                   std::string_view className,
                                   std::string_view methodName,
                                   int line)
    : BaseException("Invalid meta information!", fileName, className, methodName, line)
{}