#include "exammanager.h"
#include <QDebug>

ExamManager::ExamManager()
{

}

QVector<QString> ExamManager::getExamList()
{
    LoadData();
    return examNameList;
}

void ExamManager::AddExamination(QString examName)
{
    LoadData();
    for (int i = 0; i < examNameList.count(); i++) {
        if(examNameList.at(i) == examName) return;
    }
    examNameList.push_back(examName);
    SaveData();
}

bool ExamManager::CheckExamExist(QString examName)
{
    LoadData();

    for (int i = 0; i < examNameList.count(); i++) {
        if(examNameList.at(i) == examName) return true;
    }

    return false;
}

void ExamManager::LoadData()
{
    examNameList.clear();

    QFile examList(fileName);
    if(!examList.open(QIODevice::ReadOnly)) return;
    QByteArray b_a = examList.readAll();
    examList.close();

    QJsonDocument doc = QJsonDocument::fromJson(b_a);
    QJsonObject obj = doc.object();

    QJsonArray arr = obj["Names"].toArray();

    for (int i = 0; i < arr.count(); i++) {
        QJsonObject reg = arr[i].toObject();
        examNameList.push_back(reg["Examination"].toString());
    }
}

void ExamManager::SaveData()
{
    QJsonObject jsonObject;
    QJsonArray jsonArray;

    for (int i = 0; i < examNameList.count(); i++) {
        QJsonObject obj;
        obj["Examination"] = examNameList.at(i);
        jsonArray.push_back(obj);
    }

    jsonObject["Names"] = jsonArray;
    QByteArray b_a = QJsonDocument(jsonObject).toJson();

    QFile examList(fileName);
    examList.open(QIODevice::WriteOnly);
    examList.write(b_a);
    examList.close();
}
