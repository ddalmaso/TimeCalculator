#ifndef DATEEXCEPTION_H
#define DATEEXCEPTION_H

#include <QString>

class DateException
{
private:
    QString err_msg;
    QString err_title;
public:
    DateException(const QString&, const QString&);
    ~DateException() {}
    QString message() const;
    QString title() const;
};

#endif // DATEEXCEPTION_H
