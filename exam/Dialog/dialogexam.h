#ifndef DIALOGEXAM_H
#define DIALOGEXAM_H

#include <QDialog>
#include <QFormLayout>
#include <QPushButton>

namespace Ui {
class DialogExam;
}

class DialogExam : public QDialog
{
    Q_OBJECT

public:
    explicit DialogExam(QVector<QString> *examlist, QWidget *parent = nullptr);
    ~DialogExam();

private:
    Ui::DialogExam *ui;

    QVector<QString> *list;

signals:
    void onDialogExit(QString examName);

private slots:
    void onClicked();
};

#endif // DIALOGEXAM_H
