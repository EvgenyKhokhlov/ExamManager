#ifndef EXAMINATION_H
#define EXAMINATION_H

#include "Question\questionbase.h"
#include "Question\textquestion.h"
#include "Question\radiobuttonquestion.h"
#include "Question\checkboxquestion.h"
#include "exammanager.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QLayout>
#include <QDebug>

class Examination
{
public:
    Examination();

    void saveQuestion(QuestionBase* input, int id);
    QuestionBase *loadQuestion(int id);
    void saveExamination(QString examName, float score, bool isShow);
    Examination* loadExamination(QString examName);
    int GetQuestionCount();
    float GetTotalScore();

    float getScoreRequired() const;
    bool getShowScore() const;

private:
    QVector<QuestionBase*> questions;
    float scoreRequired = 0;
    bool showScore = false;

    QString checkQuestionType(QuestionBase *question);

    ExamManager *examManager;
};

#endif // EXAMINATION_H
