#include "dateexception.h"

DateException::DateException(const QString& title, const QString& msg):
    err_title(title), err_msg(msg) {}

QString DateException::message() const {
    return this->err_msg + " Inserire la data esatta e riprovare.";
}

QString DateException::title() const {
    return this->err_title;
}

