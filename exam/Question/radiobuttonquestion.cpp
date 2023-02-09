#include "radiobuttonquestion.h"
#include <QDebug>

RadioButtonQuestion::RadioButtonQuestion()
{

}

float RadioButtonQuestion::check(QVector<QString> input)
{
    for (int i = 0; i < answers.size(); i++) {
        if(answers.at(i).text == input.last() && answers.at(i).isCorrect)
            return price;
    }
    return 0;
}
