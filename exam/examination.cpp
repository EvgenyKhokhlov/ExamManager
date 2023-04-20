#include "examination.h"
#include <QDebug>


Examination::Examination()
{
    examManager = new ExamManager;
}

void Examination::saveQuestion(QuestionBase *input, int id)
{
    if(questions.value(id - 1) == nullptr)
        questions.push_back(input);
    else
        questions.replace(id - 1, input);
}

QuestionBase *Examination::loadQuestion(int id)
{
    for (int i = 0; i < questions.size(); i++) {
        if(questions.at(i)->getID() == id) return questions.at(i);
    }
    return nullptr;
}

void Examination::saveExamination(QString examName, float score, bool isShow)
{
    if(!QDir("examinations").exists())
        QDir().mkdir("examinations");
    
    QString address = "examinations/" + examName + ".json";
    QFile file(address);

    QJsonObject jsonObject;
    QJsonArray jsonArray;

    for (int i = 0; i < questions.count(); i++) {
        QJsonObject obj;
        QVector<Answer> answers = questions.at(i)->getAnswers();

        QJsonArray answerArray;
        for (int j = 0; j < answers.count(); j++) {
            QJsonObject answer;
            answer["AnswerText"] = answers.at(j).text;
            answer["isCorrect"] = answers.at(j).isCorrect;
            answerArray.push_back(answer);
        }
        obj["Answers"] = answerArray;
        obj["QuestionText"] = questions.at(i)->getQuestionText();
        obj["Price"] = questions.at(i)->getPrice();
        obj["PictureAddress"] = questions.at(i)->getImageAddress();
        obj["ID"] = questions.at(i)->getID();
        obj["QuestionType"] = checkQuestionType(questions.at(i));

        jsonArray.push_back(obj);
    }

    jsonObject["Questions"] = jsonArray;
    jsonObject["Score"] = score;
    jsonObject["isShow"] = isShow;

    QByteArray b_a = QJsonDocument(jsonObject).toJson();

    file.open(QIODevice::WriteOnly);
    file.write(b_a);
    file.close();
}

Examination* Examination::loadExamination(QString examName)
{
    Examination *ex = new Examination;
    if (!examManager->CheckExamExist(examName)){
        ex = nullptr;
        return ex;
    }

    QString address = "examinations/" + examName + ".json";
    QFile file(address);
    file.open(QIODevice::ReadOnly);
    QByteArray b_a;
    b_a = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(b_a);
    QJsonObject obj = doc.object();

    QJsonArray arr = obj["Questions"].toArray();

    for (int i = 0; i < arr.count(); i++) {
        QJsonObject questionObj = arr.at(i).toObject();

        QuestionBase *question;
        if(questionObj["QuestionType"] == "Text") question = new TextQuestion;
        else if(questionObj["QuestionType"] == "Check") question = new CheckBoxQuestion;
        else if(questionObj["QuestionType"] == "Radio") question = new RadioButtonQuestion;
        else continue;

        QJsonArray answerArr;
        answerArr = questionObj["Answers"].toArray();
        for (int j = 0; j < answerArr.count(); j++) {
            QJsonObject answerObj = answerArr.at(j).toObject();
            question->addAnswer(answerObj["AnswerText"].toString(), answerObj["isCorrect"].toBool());
        }
        question->setQuestionText(questionObj["QuestionText"].toString());
        question->setPrice(questionObj["Price"].toInt());
        question->setPictureAdress(questionObj["PictureAddress"].toString());
        question->setID(questionObj["ID"].toInt());

        questions.push_back(question);
    }

    scoreRequired = (float)obj["Score"].toDouble();
    showScore = obj["isShow"].toBool();

    return this;
}

int Examination::GetQuestionCount()
{
    return questions.size();
}

float Examination::GetTotalScore()
{
    float totalScore = 0;

    for (int i = 0; i < questions.count(); i++) {
        totalScore += questions.at(i)->getPrice();
    }
    return totalScore;
}

float Examination::getScoreRequired() const
{
    return scoreRequired;
}

bool Examination::getShowScore() const
{
    return showScore;
}

QString Examination::checkQuestionType(QuestionBase *question)
{
    TextQuestion *textquestion = dynamic_cast<TextQuestion*>(question);
    if(textquestion != nullptr){
        return "Text";
    }

    CheckBoxQuestion *checkBoxQuestion = dynamic_cast<CheckBoxQuestion*>(question);
    if(checkBoxQuestion != nullptr){
        return "Check";
    }

    RadioButtonQuestion *radioButQuestion = dynamic_cast<RadioButtonQuestion*>(question);
    if(radioButQuestion != nullptr){
        return "Radio";
    }
    return  nullptr;
}
