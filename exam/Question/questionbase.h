#ifndef QUESTIONBASE_H
#define QUESTIONBASE_H

#include <QString>
#include <QVector>


struct Answer{
    QString text;
    bool isCorrect = false;
};

class QuestionBase
{

public:
    QuestionBase();

    void addAnswer(QString text, bool isCorrect = false);
    void setQuestionText(QString input);
    void setPrice(float input);
    void setPictureAdress(QString input);
    void setID(int input);
    float virtual check(QVector<QString> input) = 0;

    QVector<Answer> getAnswers();
    QString getQuestionText() const;
    QString getImageAddress() const;
    float getPrice() const;
    int getID() const;

protected:
    int questionID;
    QVector<Answer> answers;
    QString questionText;
    QString imageAddress = nullptr;
    float price = 1;
};

#endif // QUESTIONBASE_H
