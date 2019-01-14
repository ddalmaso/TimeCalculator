#include "timecalculator.h"
#include "calcmanager.h"
#include <ui_timecalculator.h>
#include <QTime>
#include <QTimer>
#include <QMessageBox>

TimeCalculator::TimeCalculator(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::TimeCalculator)
{
    ui->setupUi(this);

    //Imposto il layout iniziale della form
    setFixedSize(size());

    styleFrame = "QFrame { background-color: rgb(227, 227, 227); "
                 "background-color: qlineargradient(spread:repeat, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(201, 198, 186, 255), stop:1 rgba(214, 255, 236, 255));}";

    styleLineEdit = "QLineEdit { border: 1px solid #a3a3a3; "
                    "border-radius: 2px; }";

    styleLabel = "background-color: rgba(255, 255, 255, 10);";

    styleDateTime ="QFrame { border: none; "
                   "background-color: rgb(227, 227, 227); "
                   "background-color: qlineargradient(spread:repeat, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(201, 198, 186, 255), stop:1 rgba(214, 255, 236, 255));}";

    ui->label_Time->setVisible(true);
    ui->label_DateTime->setVisible(false);
    ui->label_Date->setVisible(false);

    ui->orarioFrame->setStyleSheet(styleFrame);
    ui->buttonFrame->setStyleSheet(styleFrame);

    //Pulsanti di opzione Data, Ora e Data+Ora
    connect(ui->radioData, SIGNAL(clicked(bool)), this, SLOT(enable_dataFrame()));
    connect(ui->radioOra, SIGNAL(clicked(bool)), this, SLOT(enable_orarioFrame()));
    connect(ui->radioDataOra, SIGNAL(clicked(bool)), this, SLOT(enable_allFrame()));

    //Pulsante risultato
    connect(ui->btnCalcola, SIGNAL(clicked(bool)), this, SLOT(set_FrameResult()));

    //Data corrente
    showcurrentDate();

    //Ora attuale, visualizzata tramite timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showcurrentTime()));
    timer->start(1000);

    //Pulsanti per impostare la textbox all'ora corrente
    connect(ui->btn_inizioaOra, SIGNAL(clicked(bool)), this, SLOT(showcurrentTime()));
    connect(ui->btn_fineaOra, SIGNAL(clicked(bool)), this, SLOT(showcurrentTime()));
}

TimeCalculator::~TimeCalculator() { delete ui; }

//Abilita solo il pannello per i calcoli sulle Date
void TimeCalculator::enable_dataFrame() {
    if(ui->radioData->isChecked()) {
        ui->label_Date->setVisible(true);
        ui->label_DateTime->setVisible(false);
        ui->label_Time->setVisible(false);
        ui->dataFrame->setEnabled(true);
        ui->orarioFrame->setEnabled(false);
        ui->dataFrame->setStyleSheet(styleFrame);
        ui->orarioFrame->setStyleSheet("");
        //setRedItems(true);

    }
}

//Abilita solo il pannello per i calcoli sugli Orari
void TimeCalculator::enable_orarioFrame() {
    if(ui->radioOra->isChecked()) {
        ui->label_Date->setVisible(false);
        ui->label_DateTime->setVisible(false);
        ui->label_Time->setVisible(true);
        ui->orarioFrame->setEnabled(true);
        ui->dataFrame->setEnabled(false);
        ui->orarioFrame->setStyleSheet(styleFrame);
        ui->dataFrame->setStyleSheet("");
        //setRedItems(false);
    }
}

//Abilita sia pannello Data che pannello Orari
void TimeCalculator::enable_allFrame() {
    if(ui->radioDataOra->isChecked()) {
        ui->orarioFrame->setStyleSheet(styleDateTime);
        ui->dataFrame->setStyleSheet(styleDateTime);
        ui->label_Date->setVisible(false);
        ui->label_DateTime->setVisible(true);
        ui->label_Time->setVisible(false);
        ui->orarioFrame->setEnabled(true);
        ui->dataFrame->setEnabled(true);
        //setRedItems(true);
    }
}

void TimeCalculator::setFrame(const QString& frame) {
    if(frame == "orario") {
        QString orario_i = ui->textOraInizio->text();
        QString orario_f = ui->textOraFine->text();

        if(orario_i == "  :    :  " || orario_f == "  :    :  ")
            throw QString("Impossibile eseguire il calcolo: verificare di aver inserito le date e/o le ore dove richiesto e riprovare.");

        QString ore_i = orario_i.left(2);
        QString min_i = orario_i.section(':', 1, 1);
        QString sec_i = orario_i.right(2);

        QString ore_f = orario_f.left(2);
        QString min_f = orario_f.section(':', 1, 1);
        QString sec_f = orario_f.right(2);

        ora_inizio.setOrario(ore_i.toInt(), min_i.toInt(), sec_i.toInt());
        ora_fine.setOrario(ore_f.toInt(), min_f.toInt(), sec_f.toInt());
        diff_ora = ora_fine - ora_inizio;

        ui->textOre->setText(QString::number(diff_ora.Ore()));
        ui->textMinuti->setText(QString::number(diff_ora.Minuti()));
        ui->textSecondi->setText((QString::number(diff_ora.Secondi())));
    }

    if(frame == "data") {
        QString data_i = ui->textDataInizio->text();
        QString data_f = ui->textDataFine->text();

        if(data_i == " /  / " || data_f == " /  / ")
            throw QString("Impossibile eseguire il calcolo: verificare di aver inserito le date e/o le ore dove richiesto e riprovare.");

        QString a_i = data_i.right(4);
        QString m_i = data_i.section('/', 1, 1);
        QString g_i = data_i.left(2);

        QString a_f = data_f.right(4);
        QString m_f = data_f.section('/', 1, 1);
        QString g_f = data_f.left(2);

        data_inizio = Data(g_i.toInt(), m_i.toInt(), a_i.toInt());
        data_fine = Data(g_f.toInt(), m_f.toInt(), a_f.toInt());
        diff_data = data_fine - data_inizio;

        ui->textAnni->setText(QString::number(diff_data.Anno()));
        ui->textMesi->setText(QString::number(diff_data.Mese()));
        ui->textGiorni->setText(QString::number(diff_data.Giorno()));

        ui->textTotGiorni->setText(QString::number(diffGiorni(data_inizio, data_fine, "g")));
        ui->textSettimane->setText(QString::number(diffGiorni(data_inizio, data_fine, "g")/7));
        ui->textLavorativi->setText(QString::number(diffGiorni(data_inizio, data_fine, "l")));
        ui->textSabati->setText(QString::number(diffGiorni(data_inizio, data_fine, "s")));
        ui->textDomeniche->setText(QString::number(diffGiorni(data_inizio, data_fine,"d")));
        ui->textFestivi->setText(QString::number(diffGiorni(data_inizio, data_fine, "f")));
    }
}

//Compila correttamente i campi di testo contenuti nei rispettivi pannelli
void TimeCalculator::set_FrameResult()
{
    try {
        if(ui->radioOra->isChecked()) {
            setFrame("orario");
            int totMinuti = (diff_ora.Ore()*60) + diff_ora.Minuti();
            int totSecondi = totMinuti*60 + diff_ora.Secondi();

            ui->textOreTot->setText(QString::number(diff_ora.Ore()));
            ui->textMinutiTot->setText(QString::number(totMinuti));
            ui->textSecondiTot->setText(QString::number(totSecondi));
        }

        if(ui->radioData->isChecked()) {
            setFrame("data");
        }

        if(ui->radioDataOra->isChecked()) {
            setFrame("orario"); setFrame("data");

            DataOra dataora_inizio(ora_inizio.Ore(), ora_inizio.Minuti(), ora_inizio.Secondi(),
                                   data_inizio.Giorno(), data_inizio.Mese(), data_inizio.Anno());
            DataOra dataora_fine(ora_fine.Ore(), ora_fine.Minuti(), ora_fine.Secondi(),
                                 data_fine.Giorno(), data_fine.Mese(), data_fine.Anno());

            int totOre = oreTotali(dataora_inizio, dataora_fine);
            int totMinuti = (totOre*60 + diff_ora.Minuti());
            int totSecondi = totMinuti*60 + diff_ora.Secondi();

            ui->textOreTot->setText(QString::number(totOre));
            ui->textMinutiTot->setText(QString::number(totMinuti));
            ui->textSecondiTot->setText(QString::number(totSecondi));
        }
    }
    catch(QString& err) {
        QMessageBox::information(this, "TimeCalculator", err);
    }
    catch(TimeException& time_ex) {
        QMessageBox::information(this, time_ex.title(), time_ex.message());
    }
    catch(DateException& date_ex) {
        QMessageBox::information(this, date_ex.title(), date_ex.message());
    }
}

//Gestisce l'apertura di una nuova form
void TimeCalculator::on_btnCalcDialog_clicked()
{
    calcDialog = new CalcDialog(this);
    calcDialog->show();
}


//Visualizza l'ora corrente
void TimeCalculator::showcurrentTime() {
    QObject* obj = (QObject*) sender();
    QTime time = QTime::currentTime(); //ottengo l'ora esatta

    if(dynamic_cast<QTimer*>(obj)) {
        QString currentTime = time.toString("hh:mm:ss");
        ui->lbl_currentTime->setText(currentTime);
    }
    else {
        DataOra adesso(time.hour(), time.minute(), time.second());
        if(obj->objectName() == "btn_inizioaOra")
            ui->textOraInizio->setText(adesso.toString());
        else //btn_inizioaFine
            ui->textOraFine->setText(adesso.toString());
    }
}

//Visualizza la data corrente sulla form
void TimeCalculator::showcurrentDate() {    
    Data* now = new DataSett();
    QString curr = now->Data::toString();
    curr.insert(2, "/"); curr.insert(5, "/");
    curr = now->toString() + " " + curr;
    ui->lbl_currentDate->setText(curr);
}
