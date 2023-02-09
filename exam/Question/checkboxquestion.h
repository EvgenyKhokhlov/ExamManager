#ifndef CHECKBOXQUESTION_H
#define CHECKBOXQUESTION_H

#include "questionbase.h"

class CheckBoxQuestion: public QuestionBase
{
public:
    CheckBoxQuestion();
    float check(QVector<QString> input) override;
};

#endif // CHECKBOXQUESTION_H
