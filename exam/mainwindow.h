#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>

#include "Question\questionbase.h"
#include "Question\textquestion.h"
#include "Question\radiobuttonquestion.h"
#include "Question\checkboxquestion.h"
#include "ExamForm\exameditor.h"
#include "exammanager.h"
#include "ExamForm\exampasser.h"
#include "Dialog\dialogexam.h"
#include "Dialog\dialogpersonaldata.h"
#include "examresultmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ExamEditor *examManager;
    ExamResultManager *resultManager;
    QWidget *mainMenu;
    QWidget *examMenu;
    QWidget *examCreationMenu;
    QWidget *examEditionMenu;

    QString *examinationName;

private slots:
    void loadExaminationMenu();
    void loadExamCreationMenu();
    void loadExamChooseMenu();
    void loadExamResulMenu();
    void loadExamEditorMenu(QString examName);
    void loadPersonalDialog(QString examName);
    void loadExamPasser(QString name, QString surname, int age);
    void loadMainMenu();

};
#endif // MAINWINDOW_H
