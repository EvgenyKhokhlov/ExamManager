#ifndef EXAMFORMBASE_H
#define EXAMFORMBASE_H

#include <QWidget>
#include <QLayout>
#include <examination.h>
#include <QLineEdit>
#include <QCheckBox>
#include <QRadioButton>
#include <QPainter>

namespace Ui {
class ExamFormBase;
}

class ExamFormBase : public QWidget
{
    Q_OBJECT

public:
    explicit ExamFormBase(QWidget *parent = nullptr);
    ~ExamFormBase();

private:
    Ui::ExamFormBase *ui;

protected:
    void clearLayout(QLayout *layout);
    virtual void ClearForm();

    Examination *examination;
    QuestionBase *question;
    QString questionType = nullptr;
    QImage image;

    QLineEdit *textAnswer;
    QVector<QCheckBox*> checkBoxAnswers;
    QVector<QRadioButton*> radioButAnswers;

protected slots:
    void paintEvent(QPaintEvent *event);

signals:
    void loadMainMenu();

};

#endif // EXAMFORMBASE_H
