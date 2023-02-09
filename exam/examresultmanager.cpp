#include "examresultmanager.h"
#include "ui_examresultmanager.h"

#include <QDebug>

ExamResultManager::ExamResultManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamResultManager)
{
    ui->setupUi(this);

    table = new QTableWidget;
    table->setColumnCount(7);

    QStringList horzHeaders;
    horzHeaders << "ExamName" << "Name" << "Surname" << "Age" << "Score" << "isPassed" << "Time/Date";
    table->setHorizontalHeaderLabels(horzHeaders);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->gridLayout->addWidget(table);

    LoadData();
}

ExamResultManager::~ExamResultManager()
{
    delete ui;
}

void ExamResultManager::SaveResult(Result *input)
{
    LoadData();
    results.push_back(input);
    SaveData();
}

void ExamResultManager::on_pushButton_quit_clicked()
{
    emit loadMainMenu();
}

void ExamResultManager::LoadData()
{
    results.clear();

    QFile resultList(fileName);
    if(!resultList.open(QIODevice::ReadOnly)) return;
    QByteArray b_a = resultList.readAll();
    resultList.close();

    QJsonDocument doc = QJsonDocument::fromJson(b_a);
    QJsonObject obj = doc.object();

    QJsonArray arr = obj["Results"].toArray();

    for (int i = 0; i < arr.count(); i++) {
        QJsonObject reg = arr[i].toObject();
        result = new Result;

        result->examName = reg["ExamName"].toString();
        result->name = reg["Name"].toString();
        result->surname = reg["Surname"].toString();
        result->age = reg["Age"].toInt();
        result->score = (float)reg["Score"].toDouble();
        result->totalScore = (float)reg["TotalScore"].toDouble();
        result->isPassed = reg["isPassed"].toBool();

        QDate date = QDate::fromString(reg["Date"].toString(),"dd.MM.yyyy");
        result->date = date;

        QTime time = QTime::fromString(reg["Time"].toString(), "hh:mm");
        result->time = time;

        results.push_back(result);
    }
}

void ExamResultManager::SaveData()
{
    QJsonObject jsonObject;
    QJsonArray jsonArray;

    for (int i = 0; i < results.count(); i++) {
        QJsonObject obj;
        obj["ExamName"] = results.at(i)->examName;
        obj["Name"] = results.at(i)->name;
        obj["Surname"] = results.at(i)->surname;
        obj["Age"] = results.at(i)->age;
        obj["Score"] = results.at(i)->score;
        obj["TotalScore"] = results.at(i)->totalScore;
        obj["isPassed"] = results.at(i)->isPassed;
        obj["Date"] = results.at(i)->date.toString("dd.MM.yyyy");
        obj["Time"] = results.at(i)->time.toString("hh:mm");
        jsonArray.push_back(obj);
    }

    jsonObject["Results"] = jsonArray;
    QByteArray b_a = QJsonDocument(jsonObject).toJson();

    QFile examList(fileName);
    examList.open(QIODevice::WriteOnly);
    examList.write(b_a);
    examList.close();
}

void ExamResultManager::ShowResult()
{
    table->setRowCount(foundedResults.count());

    for (int i = 0; i < foundedResults.count(); i++) {
        table->setItem(i, 0, new QTableWidgetItem(foundedResults.at(i)->examName));
        table->setItem(i, 1, new QTableWidgetItem(foundedResults.at(i)->name));
        table->setItem(i, 2, new QTableWidgetItem(foundedResults.at(i)->surname));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(foundedResults.at(i)->age)));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(foundedResults.at(i)->score) + "/" +
                                                  QString::number(foundedResults.at(i)->totalScore)));
        table->setItem(i, 5, new QTableWidgetItem(QVariant(foundedResults.at(i)->isPassed).toString()));
        table->setItem(i, 6, new QTableWidgetItem(foundedResults.at(i)->time.toString("hh:mm") + "/" +
                                                  foundedResults.at(i)->date.toString("dd.MM.yyyy")));
    }
}

void ExamResultManager::clearForm()
{
    table->clearContents();

    ui->lineEdit_name->clear();
    ui->lineEdit_surname->clear();
    ui->lineEdit_examName->clear();
    ui->checkBox_isPassed->setChecked(false);
}



void ExamResultManager::on_pushButton_find_name_surname_clicked()
{
    if( ui->lineEdit_name->text() == nullptr && ui->lineEdit_surname->text() == nullptr)
        return;

    foundedResults.clear();

    for (int i = 0; i < results.count(); i++) {
        if(ui->lineEdit_name->text() == nullptr && results.at(i)->surname == ui->lineEdit_surname->text()){
            foundedResults.push_back(results.at(i));
            continue;
        }
        if(ui->lineEdit_surname->text() == nullptr && results.at(i)->name == ui->lineEdit_name->text()){
            foundedResults.push_back(results.at(i));
            continue;
        }
        if(results.at(i)->name == ui->lineEdit_name->text() && results.at(i)->surname == ui->lineEdit_surname->text()){
            foundedResults.push_back(results.at(i));
        }
    }
    clearForm();
    ShowResult();
}

void ExamResultManager::on_pushButton_find_isPassed_clicked()
{
    foundedResults.clear();

    for (int i = 0; i < results.count(); i++){
        if(ui->checkBox_isPassed->isChecked() == results.at(i)->isPassed)
           foundedResults.push_back(results.at(i));
    }
    clearForm();
    ShowResult();
}

void ExamResultManager::on_pushButton_find_examName_clicked()
{
    if( ui->lineEdit_examName->text() == nullptr)
        return;

    foundedResults.clear();

    for (int i = 0; i < results.count(); i++){
        if(ui->lineEdit_examName->text() == results.at(i)->examName)
           foundedResults.push_back(results.at(i));
    }
    clearForm();
    ShowResult();
}
