#include "calcdialog.h"
#include "calcmanager.h"

CalcDialog::CalcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalcDialog)
{
    ui->setupUi(this);

    //rimuove il "question mark" dal barra del titolo
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //Imposto il layout della form iniziale
    setFixedSize(size());
    styleButton = "QPushButton { background: #3498db; "
                  "background-image: linear-gradient(to bottom, #3498db, #2980b9); "
                  "border-radius: 28px; "
                  "font-family: Arial; "
                  "border: 1px solid #046baf; "
                  "font-size: 18px; "
                  "color: #ffffff; "
                  "text-decoration: none; }";
    ui->label_Data->setVisible(false);
    ui->textData1->setVisible(false);
    ui->textData2->setVisible(false);
    for(int i=0; i<4; ++i)
        ui->periodLayout->itemAt(i)->widget()->setVisible(false);
    ui->lbl_Arrow->setVisible(false);

    //Pulsanti di opzione Tempo e Data
    connect(ui->radioTime, SIGNAL(clicked(bool)), this, SLOT(enableTimeOperation()));
    connect(ui->radioDate, SIGNAL(clicked(bool)), this, SLOT(enableDateOperation()));

    //Pulsanti di somma e sottrazione
    connect(ui->btnPlus, SIGNAL(released()), this, SLOT(handleOpButton()));
    connect(ui->btnMinus, SIGNAL(released()), this, SLOT(handleOpButton()));

    //Pulsanti di opzione Giorni, Settimane, Mesi e Trimestri
    for(int i=0; i<4; ++i)
        connect(ui->periodLayout->itemAt(i)->widget(), SIGNAL(clicked(bool)), this, SLOT(setLabel2()));

    //Pulsante di chiusura
    connect(ui->btnChiudi, SIGNAL(clicked(bool)), this, SLOT(close()));

    CalcManager *calcManager = new CalcManager(ui);

    //Caselle di testo per data e ora
    connect(ui->textOra1, SIGNAL(textChanged(QString)), calcManager, SLOT(setLeftOperand()));
    connect(ui->textData1, SIGNAL(textChanged(QString)), calcManager, SLOT(setLeftOperand()));

    //Pulsanti di somma e sottrazione
    connect(ui->btnPlus, SIGNAL(clicked(bool)), calcManager, SLOT(setOperation()));
    connect(ui->btnMinus, SIGNAL(clicked(bool)), calcManager, SLOT(setOperation()));

    //Pulsante risultato
    connect(ui->btnEq, SIGNAL(clicked(bool)), calcManager, SLOT(setResult()));

    //Pulsante di reset
    connect(ui->btnReset, SIGNAL(clicked(bool)), calcManager, SLOT(resetOperation()));
}

CalcDialog::~CalcDialog()
{
    delete ui;
}

//Abilita il pannello per i calcoli sul Tempo
void CalcDialog::enableTimeOperation() {
    if(ui->radioTime->isChecked()) {
        ui->label_Tempo->setVisible(true);
        ui->label_Data->setVisible(false);
        ui->textOra1->setVisible(true);
        ui->textOra2->setVisible(true);
        ui->textData1->setVisible(false);
        ui->textData2->setVisible(false);
        ui.label_1->setText("hh : mm : ss");
        ui->label_2->setText("hh : mm : ss");
        for(int i=0; i<4; ++i)
            ui->periodLayout->itemAt(i)->widget()->setVisible(false);
        ui->lbl_Arrow->setVisible(false);
    }
}

//Abilita il pannello per i calcoli sulle Date
void CalcDialog::enableDateOperation() {
    if(ui->radioDate->isChecked()) {
        ui->label_Tempo->setVisible(false);
        ui->label_Data->setVisible(true);
        ui->textOra1->setVisible(false);
        ui->textOra2->setVisible(false);
        ui->textData1->setVisible(true);
        ui->textData2->setVisible(true);
        ui->label_1->setText("gg : mm : aaaa");
        setLabel2();
        for(int i=0; i<4; ++i)
            ui->periodLayout->itemAt(i)->widget()->setVisible(true);
        ui->lbl_Arrow->setVisible(true);
        Data now;
        ui->textData1->setText(now.toString());
    }
}

//Gestisce il layout dei pulsanti somma e sottrazione
void CalcDialog::handleOpButton() {
    QPushButton* button = (QPushButton*) sender();
    if(button->objectName() == "btnPlus") {
        ui->btnPlus->setStyleSheet(styleButton);
        ui->btnMinus->setStyleSheet("");
        ui->label_op->setText("Somma");
    }
    else {  //minus button
        ui->btnMinus->setStyleSheet(styleButton);
        ui->btnPlus->setStyleSheet("");
        ui->label_op->setText("Sottrai");
    }
}

//Aggiorna il testo della label2 in base all'opzione scelta
void CalcDialog::setLabel2() {
    if(ui->radioGiorni->isChecked())
        ui->label_2->setText("giorni");
    else if(ui->radioSettimane->isChecked())
        ui->label_2->setText("settimane");
    else if(ui->radioMesi->isChecked())
        ui->label_2->setText("mesi");
    else ui->label_2->setText("trimestri");
}


