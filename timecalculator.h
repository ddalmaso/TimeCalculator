#ifndef TIMECALCULATOR_H
#define TIMECALCULATOR_H

#include <QMainWindow>
#include "calcdialog.h"
#include "dataora.h"
#include "datasett.h"

namespace Ui {
class TimeCalculator;
}

class TimeCalculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimeCalculator(QWidget *parent = 0);
    ~TimeCalculator();
    void setFrame(const QString&);
    void setRedItems(bool value);
    void showcurrentDate();

public slots:
    void enable_dataFrame();
    void enable_orarioFrame();
    void enable_allFrame();
    void set_FrameResult();
    void showcurrentTime();

private slots:
    void on_btnCalcDialog_clicked();

private:
    Ui::TimeCalculator *ui;
    CalcDialog *calcDialog;

    DataOra ora_inizio, ora_fine, diff_ora;
    Data data_inizio, data_fine, diff_data;
    QString styleFrame, styleLabel, styleLineEdit;
    QString styleDateTime;
};

#endif // TIMECALCULATOR_H
