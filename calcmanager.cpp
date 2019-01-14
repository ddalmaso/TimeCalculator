#include "calcmanager.h"
#include "calcdialog.h"
#include "ui_calcdialog.h"
#include <QMessageBox>

CalcManager::CalcManager(Ui::CalcDialog *ui): QObject(), ui(ui), op(Plus) {}

//Memorizza l'operando di sinistra
void CalcManager::setLeftOperand() {
    try {
        if(ui->radioTime->isChecked()) {
            QString orario = ui->textOra1->text();

            QString ore = orario.left(2);
            QString min = orario.section(':', 1, 1);
            QString sec = orario.right(2);

            time_res = DataOra(ore.toInt(), min.toInt(), sec.toInt());
        }
        else {  //sono nel pannello Data
            QString data = ui->textData1->text();

            QString a = data.right(4);
            QString m = data.section('/', 1, 1);
            QString g = data.left(2);

            date_res = Data(g.toInt(), m.toInt(), a.toInt());
        }
    }
    catch(TimeException& time_ex) {
        QMessageBox::critical(0, time_ex.title(), time_ex.message());
    }
    catch(DateException& date_ex) {
        QMessageBox::critical(0, date_ex.title(), date_ex.message());
    }
}

//Memorizza il tipo di operazione scelta
void CalcManager::setOperation() {
    QPushButton* button = (QPushButton*) sender();
    if(button->objectName() == "btnPlus")
        op = Plus;
    else    //minus button
        op = Minus;

}

//Calcola il risultato dell'operazione e lo visualizza nella form
void CalcManager::setResult() {
    if(ui->radioTime->isChecked()) {
        QString orario = ui->textOra2->text();
        QString ore = orario.left(2);
        QString min = orario.section(':', 1, 1);
        QString sec = orario.right(2);

        time_operand = DataOra(ore.toInt(), min.toInt(), sec.toInt());
        doOperation();

        QString res = time_res.toString();
        ui->textOra1->setText(res);
    }
    else {
        date_operand = ui->textData2->text().toInt();
        doOperation();

        QString res = date_res.toString();
        ui->textData1->setText(res);
    }
}

//Esegue l'operazione e memorizza il risultato
void CalcManager::doOperation() {
    if(ui->radioTime->isChecked()) {
        switch(op){
        case Plus:
            time_res = time_res + time_operand;
            break;
        case Minus:
            time_res = time_res - time_operand;
            break;
        default:
            break;
        }
    }
    else {  //sono nel caso radioDate->isChecked(true)
        switch(op) {
        case Plus:
            if(ui->radioGiorni->isChecked()) {
                for(int i=0; i<date_operand; ++i)
                    date_res++;
            }
            if(ui->radioSettimane->isChecked()) {
                for(int i=0; i<7*date_operand; ++i)
                    date_res++;
            }
            if(ui->radioMesi->isChecked()) {
                for(int i=0; i<30*date_operand; ++i)
                    date_res++;
            }
            if(ui->radioTrimestri->isChecked()) {
                for(int i=0; i<90*date_operand; ++i)
                    date_res++;
            }
            break;
        case Minus:
            if(ui->radioGiorni->isChecked()) {
                for(int i=0; i<date_operand; ++i)
                    date_res--;
            }
            if(ui->radioSettimane->isChecked()) {
                for(int i=0; i<7*date_operand; ++i)
                    date_res--;
            }
            if(ui->radioMesi->isChecked()) {
                for(int i=0; i<30*date_operand; ++i)
                    date_res--;
            }
            if(ui->radioTrimestri->isChecked()) {
                for(int i=0; i<90*date_operand; ++i)
                    date_res--;
            }
            break;
        default:
            break;
        }
    }
}

//Resetta i campi e le operazioni al valore di default
void CalcManager::resetOperation() {
    time_operand = DataOra();
    date_operand = 0;
    time_res = DataOra(); //setto l'orario di default a 00.00.00
    date_res = Data(); //setto la data di default a oggi
    ui->textOra1->setText("000000");
    ui->textOra2->setText("000000");
    ui->textData1->setText(date_res.toString());
    ui->textData2->setText("");
}
