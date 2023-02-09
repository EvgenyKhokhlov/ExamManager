#ifndef EXAMEDITOR_H
#define EXAMEDITOR_H

#include <QWidget>

#include <ExamForm/examformbase.h>
#include "exammanager.h"

namespace Ui {
class ExamEditor;
}

class ExamEditor : public ExamFormBase
{
    Q_OBJECT

public:
    explicit ExamEditor(QString examName = nullptr, QWidget *parent = nullptr);
    ~ExamEditor();

private slots:
    void on_pushButton_textAnswer_clicked();
    void on_pushButton_checkBoxAnswers_clicked();
    void on_pushButton_radioButAnswers_clicked();
    void on_pushButton_addPicture_clicked();
    void on_pushButton_prevQuestion_clicked();
    void on_pushButton_nextQuestion_clicked();
    void on_pushButton_saveExamination_clicked();
    void on_pushButton_quit_clicked();

private:
    Ui::ExamEditor *ui;

    void clearForm();
    void saveData();
    void loadData();
    void clearContainers();

    QVector<QLineEdit*> checkBoxAnswersText;
    QVector<QLineEdit*> radioButAnswersText;

    QString pictureAddress = nullptr;
};

#endif // EXAMEDITOR_H
