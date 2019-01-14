#ifndef CALCDIALOG_H
#define CALCDIALOG_H

#include "QtWidgets/QDialog"

namespace Ui {
class CalcDialog;
}

class CalcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalcDialog(QWidget *parent = 0);
    ~CalcDialog();

public slots:
    void handleOpButton();
    void enableDateOperation();
    void enableTimeOperation();
    void setLabel2();

private:
    Ui::CalcDialog *ui;
    QString styleButton;
};

#endif // CALCDIALOG_H
