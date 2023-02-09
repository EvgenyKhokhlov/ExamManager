#ifndef EXAMRESULTMANAGER_H
#define EXAMRESULTMANAGER_H

#include <QDate>
#include <QWidget>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTableWidget>

namespace Ui {
class ExamResultManager;
}

struct Result{
    QString examName;
    QString name;
    QString surname;
    int age;
    float score;
    float totalScore;
    bool isPassed;
    QDate date;
    QTime time;
};

class ExamResultManager : public QWidget
{
    Q_OBJECT

public:
    explicit ExamResultManager(QWidget *parent = nullptr);
    ~ExamResultManager();

    void SaveResult(Result* input);

private slots:
    void on_pushButton_quit_clicked();

    void on_pushButton_find_name_surname_clicked();

    void on_pushButton_find_isPassed_clicked();

    void on_pushButton_find_examName_clicked();

private:
    Ui::ExamResultManager *ui;

    QTableWidget *table;
    Result* result;
    QVector<Result*> results;
    QVector<Result*> foundedResults;
    QString fileName = "exam_result.json";

    void LoadData();
    void SaveData();
    void ShowResult();
    void clearForm();

signals:
    void loadMainMenu();
};

#endif // EXAMRESULTMANAGER_H
