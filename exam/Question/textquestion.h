#ifndef TEXTQUESTION_H
#define TEXTQUESTION_H

#include "questionbase.h"

class TextQuestion: public QuestionBase
{
public:
    TextQuestion();
    void text();

    float check(QVector<QString> input) override;
};

#endif // TEXTQUESTION_H
