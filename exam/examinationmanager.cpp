#include "examinationmanager.h"
#include "ui_examinationmanager.h"

ExaminationManager::ExaminationManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExaminationManager)
{
    ui->setupUi(this);
}

ExaminationManager::~ExaminationManager()
{
    delete ui;
}

void ExaminationManager::openExamMenu(QWidget *examMenu)
{

}

void ExaminationManager::createExamination(QWidget *examCreationMenu)
{

}

void ExaminationManager::editExamination(QWidget *examEditionMenu)
{

}

void ExaminationManager::startExamination()
{

}
