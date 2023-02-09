#include "exampasser.h"
#include "ui_exampasser.h"

#include <QDebug>

ExamPasser::ExamPasser(QString name, QString surname, int age, QString examName, QWidget *parent) :
    ExamFormBase(parent),
    ui(new Ui::ExamPasser)
{
    ui->setupUi(this);

    ui->label_isPassed->hide();

    examination = new Examination;
    examination = examination->loadExamination(examName);

    totalQuestions = examination->GetQuestionCount();
    totalScore = examination->GetTotalScore();

    if(!examination->getShowScore())
        ui->label_scores->hide();
    ui->label_examName->setText(examName);

    LoadData();
}

ExamPasser::~ExamPasser()
{
    delete ui;
}

void ExamPasser::LoadData()
{
    ui->label_question->setText("Question " + QString::number(count) + "/" + QString::number(totalQuestions));
    if(!ui->label_scores->isHidden())
        ui->label_scores->setText("Scores " + QString::number(currentScores) + "/" + QString::number(totalScore));

    question = examination->loadQuestion(count);
    if(question == nullptr){
       return;
    }else{
       ui->textBrowser_questionText->setText(question->getQuestionText());

       QString pictureAddress = question->getImageAddress();
       if(pictureAddress != nullptr && image.load(pictureAddress))
            ui->screen->update();

       TextQuestion *textQuestion = dynamic_cast<TextQuestion*>(question);
       if(textQuestion != nullptr){
           questionType = "text";
           textAnswer = new QLineEdit;
           ui->AnswersLayout->addWidget(textAnswer);
       }

       CheckBoxQuestion *checkBoxQuestion = dynamic_cast<CheckBoxQuestion*>(question);
       if(checkBoxQuestion != nullptr){
           questionType = "check";
           QVector<Answer> answers = question->getAnswers();

           for (int i = 0; i < answers.size(); i++) {
               auto checkbox = new QCheckBox;
               checkBoxAnswers.push_back(checkbox);
               checkbox->setText(answers.at(i).text);
               ui->AnswersLayout->addWidget(checkbox);
           }
       }

       RadioButtonQuestion *radioButQuestion = dynamic_cast<RadioButtonQuestion*>(question);
       if(radioButQuestion != nullptr){
           questionType = "radio";
           QVector<Answer> answers = question->getAnswers();

           for (int i = 0; i < answers.size(); i++) {
               auto radioBut = new QRadioButton;
               radioButAnswers.push_back(radioBut);
               radioBut->setText(answers.at(i).text);
               ui->AnswersLayout->addWidget(radioBut);
           }
       }
    }
}

void ExamPasser::CalculateAnswers()
{
    QVector<QString> *answers;

    if (questionType == "text") {
        TextQuestion *textQuestion = dynamic_cast<TextQuestion*>(question);
        if(textQuestion != nullptr){
            answers = new QVector<QString>;
            answers->push_back(textAnswer->text());
            currentScores += textQuestion->check(*answers);
        }
    }
    if (questionType == "check") {
        CheckBoxQuestion *checkBoxQuestion = dynamic_cast<CheckBoxQuestion*>(question);
        if(checkBoxQuestion != nullptr){
            answers = new QVector<QString>;
            for (int i = 0; i < checkBoxAnswers.size(); i++) {
                if(checkBoxAnswers.at(i)->isChecked())
                    answers->push_back(checkBoxAnswers.at(i)->text());
            }
            currentScores += checkBoxQuestion->check(*answers);
        }
    }
    if (questionType == "radio") {
        RadioButtonQuestion *radioButQuestion = dynamic_cast<RadioButtonQuestion*>(question);
        if(radioButQuestion != nullptr){
            answers = new QVector<QString>;
            for (int i = 0; i < radioButAnswers.size(); i++) {
                if(radioButAnswers.at(i)->isChecked())
                    answers->push_back(radioButAnswers.at(i)->text());
            }
            currentScores += radioButQuestion->check(*answers);
        }
    }
}

void ExamPasser::ClearForm()
{
    clearLayout(ui->AnswersLayout);

    image = QImage();
    ui->screen->update();

    radioButAnswers.clear();
    checkBoxAnswers.clear();

}

void ExamPasser::SaveResult()
{
    if(ui->label_scores->isHidden())
        ui->label_scores->show();
    ui->label_scores->setText("Scores " + QString::number(currentScores) + "/" + QString::number(totalScore));

    ui->label_isPassed->show();
    if(currentScores >= examination->getScoreRequired())
        ui->label_isPassed->setText("Passed!");
    else
        ui->label_isPassed->setText("Failed!");

    //TODO Transer Result
}

void ExamPasser::on_pushButton_Next_clicked()
{
    CalculateAnswers();

    if (count >= totalQuestions) {
        SaveResult();
        ui->pushButton_Next->setEnabled(false);
        return;
    }
    ClearForm();
    count++;
    LoadData();
    if (count == totalQuestions)
        ui->pushButton_Next->setText("Finish Exam");
}

void ExamPasser::on_pushButton_quit_clicked()
{
    emit loadMainMenu();
}
