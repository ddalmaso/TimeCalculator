#include "timeexception.h"

TimeException::TimeException(const QString& title, const QString& msg):
    err_title(title), err_msg(msg) {}

QString TimeException::message() const {
    return this->err_msg + " Inserire l'orario esatto e riprovare.";
}

QString TimeException::title() const {
    return this->err_title;
}

