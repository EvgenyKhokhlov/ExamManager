#include "textquestion.h"
#include <QDebug>

TextQuestion::TextQuestion()
{

}

float TextQuestion::check(QVector<QString> input)
{
    if(input.last() == answers.last().text)
        return price;
    else
        return  0;
}
