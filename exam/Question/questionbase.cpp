#include "questionbase.h"

QuestionBase::QuestionBase()
{

}

void QuestionBase::addAnswer(QString text, bool isCorrect)
{
    Answer answer;
    answer.text = text;
    answer.isCorrect = isCorrect;
    answers.push_back(answer);
}

void QuestionBase::setQuestionText(QString input)
{
    questionText = input;
}

void QuestionBase::setPrice(float input)
{
    price = input;
}

void QuestionBase::setPictureAdress(QString input)
{
    imageAddress = input;
}

void QuestionBase::setID(int input)
{
    questionID = input;
}

QVector<Answer> QuestionBase::getAnswers()
{
    return answers;
}

QString QuestionBase::getQuestionText() const
{
    return  questionText;
}

QString QuestionBase::getImageAddress() const
{
    return imageAddress;
}

float QuestionBase::getPrice() const
{
    return price;
}

int QuestionBase::getID() const
{
    return questionID;
}


