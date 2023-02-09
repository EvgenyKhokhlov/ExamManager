#include "checkboxquestion.h"
#include <QDebug>

CheckBoxQuestion::CheckBoxQuestion()
{

}

float CheckBoxQuestion::check(QVector<QString> input)
{
    int allCorrectAnswers = 0;
    for (int i = 0; i < answers.size(); i++) {
        if (answers.at(i).isCorrect)
            allCorrectAnswers++;
    }
    float value = (int)(price / allCorrectAnswers * 10);
    float scorePerAnswer = (float)value / 10;

    int correctAnswers = 0;
    int wrongAnswers = 0;
    for (int k = 0; k < input.size(); k++) {
        for (int j = 0; j < answers.size(); j++) {
            if (input.at(k) == answers.at(j).text) {
                if(answers.at(j).isCorrect)
                    correctAnswers++;
                else
                    wrongAnswers++;
                break;
            }
        }
    }

    if(wrongAnswers > 1 || allCorrectAnswers - correctAnswers > 1)
        return 0;

    return  (correctAnswers - wrongAnswers) * scorePerAnswer;
}
