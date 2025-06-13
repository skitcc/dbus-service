#include "Exceptions.h"

BaseException::BaseException(std::string_view fileName,
                             std::string_view className,
                             std::string_view methodName) noexcept
    : m_fileName(fileName)
    , m_className(className)
    , m_methodName(methodName)
{
    std::ostringstream oss;
    oss << "Exception: " << m_msg << "\n"
        << "File: " << m_fileName << "\n"
        << "Class: " << m_className << "\n"
        << "Method: " << m_methodName << "\n";
    m_fullMessage = oss.str();
}

InvalidValueException::InvalidValueException(std::string_view fileName,
                                             std::string_view className,
                                             std::string_view methodName)
{
    m_msg = "Invalid value";
    BaseException(fileName, className, methodName);
}

UnsupportedTypeTag::UnsupportedTypeTag(std::string_view fileName,
                                       std::string_view className,
                                       std::string_view methodName)
{
    m_msg = "Unsupported type tag!";
    BaseException(fileName, className, methodName);
}

UnsupportedKeyConfiguration::UnsupportedKeyConfiguration(std::string_view fileName,
                                                         std::string_view className,
                                                         std::string_view methodName)
{
    m_msg = "Unsupported key!";
    BaseException(fileName, className, methodName);
}

FileException::FileException(std::string_view fileName,
                             std::string_view className,
                             std::string_view methodName)
{
    m_msg = "Error while interracting with file!";
    BaseException(fileName, className, methodName);
}

NoTypeTagException::NoTypeTagException(std::string_view fileName,
                                       std::string_view className,
                                       std::string_view methodName)
{
    m_msg = "Error : No type tag!";
    BaseException(fileName, className, methodName);
}

UnsupportedConfiguration::UnsupportedConfiguration(std::string_view fileName,
                                                   std::string_view className,
                                                   std::string_view methodName)
{
    m_msg = "Error : Unsupported Configuration!";
    BaseException(fileName, className, methodName);
}

MetaSectionError::MetaSectionError(std::string_view fileName,
                                   std::string_view className,
                                   std::string_view methodName)
{
    m_msg = "Error : invalid meta information!";
    BaseException(fileName, className, methodName);
}
