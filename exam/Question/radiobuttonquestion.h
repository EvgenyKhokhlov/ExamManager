#ifndef RADIOBUTTONQUESTION_H
#define RADIOBUTTONQUESTION_H

#include "questionbase.h"

class RadioButtonQuestion: public QuestionBase
{
public:
    RadioButtonQuestion();

    float check(QVector<QString> input) override;
};

#endif // RADIOBUTTONQUESTION_H
