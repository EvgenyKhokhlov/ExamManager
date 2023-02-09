#ifndef DIALOGPERSONALDATA_H
#define DIALOGPERSONALDATA_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class DialogPersonalData;
}

class DialogPersonalData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPersonalData(QWidget *parent = nullptr);
    ~DialogPersonalData();

private slots:
    void on_pushButton_start_clicked();

private:
    Ui::DialogPersonalData *ui;

signals:
    void onDialogExit(QString name, QString surname, int age);
};

#endif // DIALOGPERSONALDATA_H
