#ifndef CALCMANAGER_H
#define CALCMANAGER_H

#include <QObject>
#include <QString>
#include "dataora.h"

enum Operation { Plus, Minus };

namespace Ui {
class CalcDialog;
}

class CalcManager : public QObject
{
    Q_OBJECT
public:
    CalcManager(Ui::CalcDialog *ui);
    void doOperation();

private:
    Ui::CalcDialog *ui;
    DataOra time_operand;
    int date_operand;
    DataOra time_res;
    Data date_res;
    Operation op;

public slots:  
    void setLeftOperand();
    void setOperation();
    void setResult();
    void resetOperation();
};

#endif // CALCMANAGER_H
