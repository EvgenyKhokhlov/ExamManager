#include "exameditor.h"
#include "ui_exameditor.h"

#include <QPainter>
#include <QDebug>

ExamEditor::ExamEditor(QString examName, QWidget *parent) :
    ExamFormBase(parent),
    ui(new Ui::ExamEditor)
{
    ui->setupUi(this);

    ui->lineEdit_pictureAddress->setPlaceholderText("image/image.jpg");
    ui->lineEdit_scoreRequired->setValidator( new QIntValidator(0, 100, this) );
    ui->lineEdit_scoreRequired->setText("1");

    examination = new Examination;

    if(examName != nullptr){
        examination = examination->loadExamination(examName);
        loadData();
        ui->checkBox_showScore->setChecked(examination->getShowScore());
        ui->lineEdit_scoreRequired->setText(QString::number((int)examination->getScoreRequired()));
        ui->lineEdit_examName->setText(examName);
    }
}

ExamEditor::~ExamEditor()
{
    delete ui;
}

void ExamEditor::on_pushButton_textAnswer_clicked()
{
    questionType = "text";
    clearLayout(ui->AnswersLayout);

    ui->label_questionInfo->setText("Enter Correct Answer");
    textAnswer = new QLineEdit;

    ui->AnswersLayout->addWidget(textAnswer);
}

void ExamEditor::on_pushButton_checkBoxAnswers_clicked()
{
    clearContainers();

    questionType = "checkBox";
    clearLayout(ui->AnswersLayout);

    ui->label_questionInfo->setText("Choose All Correct Answers");

    for (int i = 0; i < ui->spinBox_checkBoxAnswers->value(); i++) {
        auto checkbox = new QCheckBox;
        auto lineEdit = new QLineEdit;

        checkBoxAnswers.push_back(checkbox);
        checkBoxAnswersText.push_back(lineEdit);

        ui->AnswersLayout->addRow(checkbox, lineEdit);
    }
}

void ExamEditor::on_pushButton_radioButAnswers_clicked()
{
    clearContainers();

    questionType = "radioBut";
    clearLayout(ui->AnswersLayout);

    ui->label_questionInfo->setText("Choose One Correct Answer");

    for (int i = 0; i < ui->spinBox_radioButAnswers->value(); i++) {
        auto radioBut = new QRadioButton;
        auto lineEdit = new QLineEdit;

        radioButAnswers.push_back(radioBut);
        radioButAnswersText.push_back(lineEdit);

        ui->AnswersLayout->addRow(radioBut, lineEdit);
    }
}

void ExamEditor::on_pushButton_addPicture_clicked()
{
    if(ui->lineEdit_pictureAddress->text().isEmpty())
        return;

    if(image.load(ui->lineEdit_pictureAddress->text())){
        pictureAddress = ui->lineEdit_pictureAddress->text();
        ui->screen->update();
    }
    else ui->lineEdit_pictureAddress->setText("Wrong Address");
}

void ExamEditor::on_pushButton_prevQuestion_clicked()
{
    saveData();
    clearForm();

    ui->label_questionNumber->setText(QString::number(ui->label_questionNumber->text().toInt() - 1));
    if(ui->label_questionNumber->text().toInt() <= 1) ui->pushButton_prevQuestion->setEnabled(false);
    loadData();
}

void ExamEditor::on_pushButton_nextQuestion_clicked()
{

    if (questionType == nullptr) return;

    saveData();
    clearForm();

    ui->label_questionNumber->setText(QString::number(ui->label_questionNumber->text().toInt() + 1));
    ui->pushButton_prevQuestion->setEnabled(true);
    loadData();
}

void ExamEditor::on_pushButton_saveExamination_clicked()
{
    if(ui->lineEdit_examName->text() == nullptr) return;

    saveData();
    examination->saveExamination(ui->lineEdit_examName->text(), ui->lineEdit_scoreRequired->text().toFloat(),
                                 ui->checkBox_showScore->isChecked());

    ExamManager ex;
    ex.AddExamination(ui->lineEdit_examName->text());

    emit loadMainMenu();
}

void ExamEditor::on_pushButton_quit_clicked()
{
    emit loadMainMenu();
}

void ExamEditor::clearForm()
{
    ui->textEdit_questionText->clear();
    ui->lineEdit_pictureAddress->clear();
    ui->spinBox_questionScore->setValue(1);
    ui->spinBox_checkBoxAnswers->setValue(2);
    ui->spinBox_radioButAnswers->setValue(2);

    ui->label_questionInfo->clear();
    clearLayout(ui->AnswersLayout);

    pictureAddress = nullptr;
    ExamFormBase::ClearForm();
}

void ExamEditor::clearContainers()
{
    radioButAnswers.clear();
    radioButAnswersText.clear();
    checkBoxAnswers.clear();
    checkBoxAnswersText.clear();
}

void ExamEditor::saveData()
{
    if (questionType == "text") {
        question = new TextQuestion;
        question->addAnswer(textAnswer->text());
    }
    if (questionType == "checkBox") {
        question = new CheckBoxQuestion;
        for (int i = 0; i < checkBoxAnswers.size(); i++) {
            question->addAnswer(checkBoxAnswersText.at(i)->text(), checkBoxAnswers.at(i)->isChecked());
        }
    }
    if (questionType == "radioBut") {
        question = new RadioButtonQuestion;
        for (int i = 0; i < radioButAnswers.size(); i++) {
            question->addAnswer(radioButAnswersText.at(i)->text(), radioButAnswers.at(i)->isChecked());
        }
    }
    question->setPrice(ui->spinBox_questionScore->value());
    question->setQuestionText(ui->textEdit_questionText->toPlainText());
    question->setID(ui->label_questionNumber->text().toInt());
    if(!pictureAddress.isNull()) question->setPictureAdress(pictureAddress);

    clearContainers();

    examination->saveQuestion(question, ui->label_questionNumber->text().toInt());

}

void ExamEditor::loadData()
{
    question = examination->loadQuestion(ui->label_questionNumber->text().toInt());
    if(question == nullptr){
       return;
    }else{
       ui->textEdit_questionText->setText(question->getQuestionText());
       ui->spinBox_questionScore->setValue(question->getPrice());

       if(question->getImageAddress() != nullptr){
           ui->lineEdit_pictureAddress->setText(question->getImageAddress());
           on_pushButton_addPicture_clicked();
       }

       TextQuestion *textquestion = dynamic_cast<TextQuestion*>(question);
       if(textquestion != nullptr){
           on_pushButton_textAnswer_clicked();
           textAnswer->setText(question->getAnswers().last().text);
       }

       CheckBoxQuestion *checkBoxQuestion = dynamic_cast<CheckBoxQuestion*>(question);
       if(checkBoxQuestion != nullptr){
           QVector<Answer> answers = question->getAnswers();
           ui->spinBox_checkBoxAnswers->setValue(answers.size());
           on_pushButton_checkBoxAnswers_clicked();

           for (int i = 0; i < answers.size(); i++) {
               checkBoxAnswers.at(i)->setChecked(answers.at(i).isCorrect);
               checkBoxAnswersText.at(i)->setText(answers.at(i).text);
           }
       }

       RadioButtonQuestion *radioButQuestion = dynamic_cast<RadioButtonQuestion*>(question);
       if(radioButQuestion != nullptr){
            QVector<Answer> answers = question->getAnswers();
            ui->spinBox_radioButAnswers->setValue(question->getAnswers().size());
            on_pushButton_radioButAnswers_clicked();

            for (int i = 0; i < answers.size(); i++) {
                if(answers.at(i).isCorrect) radioButAnswers.at(i)->setChecked(true);
                radioButAnswersText.at(i)->setText(answers.at(i).text);
            }
       }
    }
}








