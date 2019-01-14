#ifndef TIMEEXCEPTION_H
#define TIMEEXCEPTION_H

#include <QString>

class TimeException
{
private:
    QString err_msg;
    QString err_title;
public:    
    TimeException(const QString&, const QString&);
    ~TimeException() {}
    QString message() const;
    QString title() const;
};

#endif // TIMEEXCEPTION_H
