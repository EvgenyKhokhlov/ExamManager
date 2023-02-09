#ifndef EXAMPASSER_H
#define EXAMPASSER_H

#include <QWidget>

#include <ExamForm/examformbase.h>
#include "examresultmanager.h"

namespace Ui {
class ExamPasser;
}

class ExamPasser : public ExamFormBase
{
    Q_OBJECT

public:
    explicit ExamPasser(QString name, QString surname, int age, QString examName, QWidget *parent = nullptr);
    ~ExamPasser();

private:
    Ui::ExamPasser *ui;

    int count = 1;
    float currentScores = 0;
    float totalScore;
    int totalQuestions;
    Result *result;

    void LoadData();
    void CalculateAnswers();
    void ClearForm() override;
    void SaveResult();

private slots:
    void on_pushButton_quit_clicked();
    void on_pushButton_Next_clicked();
};

#endif // EXAMPASSER_H
