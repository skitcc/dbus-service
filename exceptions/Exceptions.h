#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <exception>
#include <string>
#include <sstream>


class BaseException : public std::exception {
public:
    BaseException() = default;
    BaseException(std::string_view fileName, std::string_view className, 
                    std::string_view methodName) noexcept;

    const char* what() const noexcept override {
        return m_fullMessage.c_str();
    }

protected:
    std::string_view m_msg;        
    std::string_view m_fileName;   
    std::string_view m_className;  
    std::string_view m_methodName; 
    std::string_view m_line;       
    std::string m_fullMessage;  
};


class InvalidValueException : public BaseException {
public:
    InvalidValueException(std::string_view fileName, std::string_view className, std::string_view methodName);
};

class UnsupportedTypeTag : public BaseException {
public:
    UnsupportedTypeTag(std::string_view fileName, std::string_view className, std::string_view methodName);
};


class UnsupportedKeyConfiguration : public BaseException {
public:
    UnsupportedKeyConfiguration(std::string_view fileName, std::string_view className, std::string_view methodName);
};

class FileException : public BaseException {
public:
    FileException(std::string_view fileName, std::string_view className, std::string_view methodName);
};
    

class NoTypeTagException : public BaseException {
public:
    NoTypeTagException(std::string_view fileName, std::string_view className, std::string_view methodName);
};

class UnsupportedConfiguration : public BaseException {
public:
    UnsupportedConfiguration(std::string_view fileName, std::string_view className, std::string_view methodName);
};

class MetaSectionError : public BaseException {
public:
    MetaSectionError(std::string_view fileName, std::string_view className, std::string_view methodName);
};


#endif