#pragma once

#include <exception>
#include <QString>

class MyException: public std::exception
{
private:
    QString _msg;

public:
    MyException(const QString & msg) : _msg(msg) {}

    virtual const char * what() const throw()
    {
        return _msg.toStdString().c_str();
    }
};