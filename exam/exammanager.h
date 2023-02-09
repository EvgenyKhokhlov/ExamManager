#ifndef EXAMMANAGER_H
#define EXAMMANAGER_H

#include <QFile>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class ExamManager
{
public:
    ExamManager();

    QVector<QString> getExamList();
    void AddExamination(QString examName);
    bool CheckExamExist(QString examName);

private:
    QString fileName = "exam_list.json";
    QVector<QString> examNameList;

    void LoadData();
    void SaveData();
};

#endif // EXAMMANAGER_H
