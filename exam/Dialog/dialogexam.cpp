#include "dialogexam.h"
#include "ui_dialogexam.h"

DialogExam::DialogExam(QVector<QString> *examlist, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExam)
{
    ui->setupUi(this);

    list = examlist;
    //TODO Сделать нормальную таблицу для кнопок
    auto layout = new QGridLayout();

    for (int i = 0; i < examlist->size(); i++) {
        auto button = new QPushButton(examlist->at(i));
        connect(button, &QPushButton::clicked, this, &DialogExam::onClicked);
        layout->addWidget(button);
    }

    setLayout(layout);
}

DialogExam::~DialogExam()
{
    delete ui;
}

void DialogExam::onClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if( button != nullptr ){
        emit onDialogExit(button->text());
        this->accept();
    }
}
