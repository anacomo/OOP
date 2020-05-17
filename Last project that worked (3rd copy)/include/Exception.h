#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>
#include <string>

class Exception : public std::exception
{
private:
    std::string errorType;

public:
    Exception(std::string error) : errorType(error)
    {
    }

    ~Exception() throw() {}
    virtual const char *what() throw()
    {
        return this->errorType.c_str();
    }
};

#endif // __EXCEPTION_H__