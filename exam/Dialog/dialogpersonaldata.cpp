#include "dialogpersonaldata.h"
#include "ui_dialogpersonaldata.h"

DialogPersonalData::DialogPersonalData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPersonalData)
{
    ui->setupUi(this);

    ui->lineEdit_age->setValidator( new QIntValidator(0, 100, this) );
}

DialogPersonalData::~DialogPersonalData()
{
    delete ui;
}

void DialogPersonalData::on_pushButton_start_clicked()
{
    QString warningMessage("Enter All Data");

    if(ui->lineEdit_name->text() == nullptr){
        ui->label_warning->setText(warningMessage);
        return;
    }
    if(ui->lineEdit_surname->text() == nullptr){
        ui->label_warning->setText(warningMessage);
        return;
    }
    if(ui->lineEdit_age->text() == nullptr){
        ui->label_warning->setText(warningMessage);
        return;
    }

    emit onDialogExit(ui->lineEdit_name->text(),
                      ui->lineEdit_surname->text(),
                      ui->lineEdit_age->text().toInt());
    this->accept();
}
